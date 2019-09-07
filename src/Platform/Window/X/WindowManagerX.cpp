//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/keysymdef.h>
#include <X11/cursorfont.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include <string>
#include <climits>
#include <thread>
#include <cstring>
#include <memory>
#include <vector>
#include <iostream>

#include "WindowManagerX.h"
#include "../WindowManager.h"
#include "../../../Events/Mouse/MouseState.h"
#include "../../../Events/Keyboard/KeyboardState.h"
#include "../../../Events/Window/WindowState.h"
#include "Exceptions/XException.h"
#include "../../../Events/Mouse/DefaultMouseStateBuilder.h"
#include "../../../Events/Mouse/MouseStateBuilder.h"
#include "../../../Events/Window/DefaultWindowStateBuilder.h"
#include "../../../Events/Window/WindowStateBuilder.h"
#include "../../../Events/Keyboard/KeyboardStateBuilder.h"
#include "../../../Events/Keyboard/DefaultKeyboardStateBuilder.h"
#include "../../../Events/Keyboard/KeyboardState.h"
#include "../../../Events/Keyboard/Key.h"
#include "../../../Events/Keyboard/DKey.h"
#include "../../../Events/Keyboard/Keyboard.h"
#include "../../../Events/Mouse/Mouse.h"
#include "Util/XDefaultKeyboardConverter.h"
#include "Util/XKeyboardConverter.h"

using std::shared_ptr;
using std::vector;
using std::string;

using namespace dengine;

int WindowManagerX::xkbEventType = 0;
Atom WindowManagerX::wmProtocols = 0;

WindowManagerX::WindowManagerX(int x, int y, uint width, uint height, const std::string& title):title(title) {
    display = XOpenDisplay(nullptr);

    if (display) {
        rootWindow = XDefaultRootWindow(display);
        visualInfo = new XVisualInfo();

        int result = XMatchVisualInfo(display, DEFAULT_SCREEN, VISUAL_DEPTH, TrueColor, visualInfo);

        if (result) {
            Colormap colorMap = XCreateColormap(display, rootWindow, visualInfo->visual, AllocNone);

            long eventsMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                              Button1MotionMask | Button2MotionMask | Button3MotionMask |
                              Button4MotionMask | Button5MotionMask | ButtonMotionMask | FocusChangeMask;

            XSetWindowAttributes xSetWindowAttributes;

            xSetWindowAttributes.colormap = colorMap;
            xSetWindowAttributes.event_mask = eventsMask;
            xSetWindowAttributes.background_pixel = XBlackPixel(display, DEFAULT_SCREEN);

            window = XCreateWindow(display, rootWindow, x, y, width, height, DEFAULT_WINDOW_DEPTH, visualInfo->depth,
                                   InputOutput, visualInfo->visual, CWColormap | CWEventMask | CWBackPixel, &xSetWindowAttributes);

            xSizeHints = XAllocSizeHints();

            setVisible(true);

            lastX = x; lastY = y;
            lastWidth = width; lastHeight = height;
            lastState = NORMAL;

            setPosition(x, y);
            setTitle(title);
            setSize(width, height);
            setCursorVisible(true);
            setDecorated(true);

            glXContext = glXCreateContext(display, visualInfo, nullptr, GL_TRUE);

            if (glXContext) {
                result = glXMakeCurrent(display, window, glXContext);

                if (result) {
                    wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", false);
                    wmProtocols = XInternAtom(display, "WM_PROTOCOLS", false);

                    XSetWMProtocols(display, window, &wmDeleteWindow, 1);

                    XkbQueryExtension(display, nullptr, &xkbEventType, nullptr, nullptr, nullptr);
                    XkbSelectEvents(display, XkbUseCoreKbd, XkbAllEventsMask, XkbAllEventsMask);
                    XkbSetDetectableAutoRepeat(display, True, nullptr);

                    xKeyboardConverter = std::make_shared<XDefaultKeyboardConverter>();
                    xKeyboardConverter->initialize(display);
                } else
                    throw XException("Unable to attach GLX context to window");
            } else
                throw XException("Unable to create GLX context");
        } else
            throw XException("No suitable XVisualInfo");
    } else
        throw XException("Could not open X display connection");
}

//@todo blinking problem
//@todo problem with reset of state (fullscreen, iconic) after it's call
void WindowManagerX::setVisible(bool isVisible) {
    if (isVisible)
        XMapWindow(display, window);
    else
        XUnmapWindow(display, window);

    mIsVisible = isVisible;

    XFlush(display);
}

void WindowManagerX::setDecorated(bool isDecorated) {
    vector<int> position = getPosition();

    Atom type = XInternAtom(display,"_NET_WM_WINDOW_TYPE", False);
    Atom value = isDecorated?XInternAtom(display,"_NET_WM_WINDOW_TYPE_NORMAL", False):
                 XInternAtom(display,"_NET_WM_WINDOW_TYPE_SPLASH", False);

    XChangeProperty(display, window, type, XA_ATOM, 32, PropModeReplace, (unsigned char*)&value, 1);

    setPosition(position[0], position[1]);

    mIsDecorated = isDecorated;
}

void WindowManagerX::setCursorVisible(bool isVisible) {
    if (isVisible) {
        XUndefineCursor(display, window);
    } else {
        Pixmap transparentCursor = XCreatePixmap(display, window, 1, 1, 1); //width, height, depth
        GC gc = XCreateGC(display, transparentCursor, 0, {});

        XSetForeground(display, gc, 0); //zero for mask (0 - invisible, 1 - visible)
        // zero for pixmap (0 - background, 1 - foreground)
        XDrawPoint(display, transparentCursor, gc, 0, 0);//x,y

        XColor anonymousColor;
        Cursor cursor = XCreatePixmapCursor(display, transparentCursor, transparentCursor, &anonymousColor, &anonymousColor, 0, 0);

        XDefineCursor(display, window, cursor);
    }

    mIsCursorVisible = isVisible;

    XFlush(display);
}

void WindowManagerX::setPosition(int x, int y) {
    setWindowBounds(x, y, 0, 0, true, false);

    XFlush(display);
}

void WindowManagerX::setSize(uint width, uint height) {
    setWindowBounds(0, 0, width, height, false, true);

    XFlush(display);
}

void WindowManagerX::setIcon(const long* buffer, int length) {
    //https://stackoverflow.com/questions/10699927/xlib-argb-window-icon
    Atom icon = XInternAtom(display, "_NET_WM_ICON", False);
    Atom typeCardinal = XInternAtom(display, "CARDINAL", False);

    XChangeProperty(display, window, icon, typeCardinal, 32, PropModeReplace, (const unsigned char*)buffer, length);

    XFlush(display);
}

void WindowManagerX::setRatio(uint ratioX, uint ratioY) {
    setSizeHints(0, 0, 0, 0, ratioX, ratioY, false, false, true);
}

void WindowManagerX::setTrayIcon(const long *buffer, int length) {

}

void WindowManagerX::setTrayName(const string &name) {

}

void WindowManagerX::sendNotification(const string &message) {

}

void WindowManagerX::setTitle(const string &title) {
    Atom wmName = XInternAtom(display, "_NET_WM_NAME", False);
    Atom utf8String = XInternAtom(display, "UTF8_STRING", False);

    XChangeProperty(display, window, wmName, utf8String, 8, PropModeReplace, (const unsigned char*)(title.c_str()), (int)title.size());

    XFlush(display);
}

void WindowManagerX::setMinimumSize(uint minimumWidth, uint minimumHeight) {
    setSizeHints(minimumWidth, minimumHeight, 0, 0, 0, 0, true, false, false);
}

void WindowManagerX::setMaximumSize(uint maximumWidth, uint maximumHeight) {
    setSizeHints(0, 0, maximumWidth, maximumHeight, 0, 0, false, true, false);
}

void WindowManagerX::setGeometryState(int windowGeometryState) {
    long data[5];

    std::fill(data, data + 5, 0);


    switch (windowGeometryState) {
        case NORMAL: {
            data[0] = NormalState;

            sendEvent(ClientMessage, "WM_CHANGE_STATE", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
                      window,
                      rootWindow);

            //hack for GNOME
            //https://stackoverflow.com/questions/30192347/how-to-restore-a-window-with-xlib

            data[0] = 1;
            data[1] = CurrentTime;

            sendEvent(ClientMessage, "_NET_ACTIVE_WINDOW", 32, data,  SubstructureRedirectMask | SubstructureNotifyMask,
                      window,
                      rootWindow);

            break;
        }

        case ICONIFIED: {
            data[0] = IconicState;

            sendEvent(ClientMessage, "WM_CHANGE_STATE", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
                      window,
                      rootWindow);

            break;
        }

        case HIDDEN_TO_TRAY: {
            //beta support. DO NOT RELY ON THIS CODE
            //TRAY only for wm which supports xembed specification

            data[0] = CurrentTime;
            data[1] = 0;//request of dock
            data[2] = window;
            data[3] = 0;
            data[4] = 0;

            char trayNumber[80] = "_NET_SYSTEM_TRAY_S";

            char number[2];

            number[0] = (char)('0' + DEFAULT_SCREEN); //count of screens should be less than 10
            number[1] = '\0';

            char resultTrayNumber[80];

            strcat(resultTrayNumber, trayNumber);
            strcat(resultTrayNumber, number);

            Atom traySelectionAtom = XInternAtom(display, resultTrayNumber, False);

            Window tray = XGetSelectionOwner(display, traySelectionAtom);

            if (tray)
                sendEvent(ClientMessage, "_NET_SYSTEM_TRAY_OPCODE", 32, data, NoEventMask, window, tray);
            else
                throw XException("Tray specification is not supported");

            break;
        }
    }

    XFlush(display);
}

void WindowManagerX::setFullscreenEnabled(bool isFullscreenEnabled) {
    long data[5];

    data[0] = isFullscreenEnabled; //add - 1, remove - 0
    data[1] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    std::fill(data + 2, data + 5, 0);

    sendEvent(ClientMessage, "_NET_WM_STATE", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
              window,
              rootWindow);

    XFlush(display);
}

void WindowManagerX::setMaximizationState(int maximization) {
    switch (maximization) {
        case NORMAL: {
            Atom atoms[3] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False),
                          XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False),
                          XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_BOTH", False)};

            setMaximized(false, atoms, 3);

            break;
        }

        case MAXIMIZED_HORIZONTAL: {
            Atom unset[2] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False),
                             XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_BOTH", False)};

            Atom set[1] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False)};

            setMaximized(false, unset, 2);
            setMaximized(true, set, 1);

            break;
        }

        case MAXIMIZED_VERTICAL: {
            Atom unset[2] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False),
                             XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_BOTH", False)};

            Atom set[1] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False)};

            setMaximized(false, unset, 2);
            setMaximized(true, set, 1);

            break;
        }

        case MAXIMIZED_BOTH: {
            Atom unset[2] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False),
                             XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False)};

            Atom set[1] = {XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_BOTH", False)};

            setMaximized(false, unset, 2);
            setMaximized(true, set, 1);

            break;
        }
    }

    XFlush(display);
}

void WindowManagerX::center() {
    vector<uint> resolution = getScreenResolution();
    vector<uint> size = getSize();

    setPosition((resolution[0] - size[0]) / 2, (resolution[1] - size[1]) / 2);
}

void WindowManagerX::focus() { //it doesnt raise window
    long data[5];
    std::fill(data, data + 5, 0);

    data[0] = 2;//from pager
    data[1] = 0;// time MUST be exactly ZERO (0), not XInternAtom(display, "_NET_WM_USER_TIME", False), not 1, only ZERO

    sendEvent(ClientMessage, "_NET_ACTIVE_WINDOW", 32, data,
              SubstructureRedirectMask | SubstructureNotifyMask, window, rootWindow);

    XFlush(display);
}

void WindowManagerX::destroy() {
    XDestroyWindow(display, window);

    XFree(visualInfo);
    XFree(xSizeHints);

    XCloseDisplay(display);
}

std::vector<uint> WindowManagerX::getScreenResolution() {
    return {(uint)XDisplayWidth(display, DEFAULT_SCREEN), (uint)XDisplayHeight(display, DEFAULT_SCREEN)};
}

bool WindowManagerX::isVisible() const {
    return mIsVisible;
}

bool WindowManagerX::isDecorated() const {
    return mIsDecorated;
}

bool WindowManagerX::isCursorVisible() const {
    return mIsCursorVisible;
}

vector<int> WindowManagerX::getPosition() const {
    vector<int> pos = getClientAreaPosition();

    int x, y;

    Window win;

    XTranslateCoordinates(display, window, rootWindow, pos[0], pos[1], &x, &y, &win);

    return {x - pos[0], y - pos[1]};
}

vector<int> WindowManagerX::getClientAreaPosition() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    return {xWindowAttributes.x, xWindowAttributes.y};
}

vector<uint> WindowManagerX::getSize() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    return {(uint)xWindowAttributes.width, (uint)xWindowAttributes.height};
}

std::vector<uint> WindowManagerX::getRatio() const {
    XSizeHints xSizeHints;

    XGetNormalHints(display, window, &xSizeHints);

    return {(uint)xSizeHints.min_aspect.x, (uint)xSizeHints.min_aspect.y};
}

const std::string& WindowManagerX::getTitle() const {
    return title;
}

vector<uint> WindowManagerX::getMinimumSize() const {
    XSizeHints xSizeHints;

    XGetNormalHints(display, window, &xSizeHints);

    return {(uint)xSizeHints.min_width, (uint)xSizeHints.min_height};
}

vector<uint> WindowManagerX::getMaximumSize() const {
    XSizeHints xSizeHints;

    XGetNormalHints(display, window, &xSizeHints);

    return {(uint)xSizeHints.max_width, (uint)xSizeHints.max_height};
}

int WindowManagerX::getGeometryState() const {
    //check if the window was trayed

    PropertyData result = getProperty("WM_STATE", window);

    if (find(IconicState, result)) return ICONIFIED;


    PropertyData result2 = getProperty("_NET_WM_STATE", window); //if old WM_STATE is not supported (but if it's so, user
    //wouldn't to programmatically iconify the window)

    Atom hidden = XInternAtom(display, "_NET_WM_STATE_HIDDEN", False);

    if (find(hidden, result2)) return ICONIFIED;

    return NORMAL;
}

bool WindowManagerX::isFullscreenEnabled() const {
    PropertyData result2 = getProperty("_NET_WM_STATE", window);

    return find(XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False), result2);
}

int WindowManagerX::getMaximizationState() const {
    PropertyData result = getProperty("_NET_WM_STATE", window);

    bool maximizedHorz = find(XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False), result);
    bool maximizedVert = find(XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False), result);
    bool maximizedBoth = find(XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_BOTH", False), result);

    if (maximizedBoth || (maximizedHorz && maximizedVert)) return MAXIMIZED_BOTH;
    else if (maximizedHorz) return MAXIMIZED_HORIZONTAL;
    else if (maximizedVert) return MAXIMIZED_VERTICAL;
    else return NORMAL;
}

bool WindowManagerX::isFocused() const {
    PropertyData data = getProperty("_NET_ACTIVE_WINDOW", rootWindow);
    long focusedWindowId = ((long*)data.data)[0];

    return focusedWindowId == window;
}

//@todo logging
//@todo tests

std::shared_ptr<MouseState> WindowManagerX::getMouseState() const {
    std::shared_ptr<MouseStateBuilder> builder(new DefaultMouseStateBuilder());

    Window win;

    int x, y, stub;
    unsigned mask;

    XQueryPointer(display, window, &win, &win, &stub, &stub, &x, &y, &mask);

    builder->setPosition(x, y);

    XEvent xEvent;

    while (XCheckMaskEvent(display, ButtonPressMask | ButtonReleaseMask, &xEvent)) {
        switch(xEvent.type) {
            case ButtonPress:
                switch (xEvent.xbutton.button) {
                    case DEFAULT_WHEEL_POSITIVE_BUTTON:
                        builder->setWheelDirection(1);

                        break;
                    case DEFAULT_WHEEL_NEGATIVE_BUTTON:
                        builder->setWheelDirection(-1);

                        break;
                    default:
                        builder->addPressedButton(toDMouseButton(xEvent.xbutton.button));
                }

                break;
            case ButtonRelease:
                builder->addReleasedButton(toDMouseButton(xEvent.xbutton.button));

                break;
        }
    }

    return builder->build();
}

std::shared_ptr<KeyboardState> WindowManagerX::getKeyboardState() const {
    std::shared_ptr<KeyboardStateBuilder> builder(new DefaultKeyboardStateBuilder());

    XEvent xEvent;

    while(XCheckIfEvent(display, &xEvent, &WindowManagerX::selectKeyboardEventsPredicate, 0)) {
        switch (xEvent.type) {
            case KeyPress:
                builder->addPressedKey(toDKey(&xEvent));

                break;
            case KeyRelease:
                builder->addReleasedKey(toDKey(&xEvent));

                break;
            default:
                if (xEvent.type == xkbEventType) {
                    XkbEvent *xkbEvent = (XkbEvent*) &xEvent;

                    switch (xkbEvent->any.xkb_type) {
                        case XkbStateNotify:
                            int lang = xkbEvent->state.group;

                            xKeyboardConverter->setGroup(lang);
                    }
                }

                break;
        }
    }

    //setLayoutName setLayoutCode are not supported by this fking WindowManagerX

    return builder->build();
}

Bool WindowManagerX::selectKeyboardEventsPredicate(Display *display, XEvent *xEvent, XPointer arg) {
    int types[] = {KeyPress, KeyRelease, xkbEventType};

    return selectEventsPredicate(xEvent, types, 3);
}

int WindowManagerX::selectEventsPredicate(XEvent *xEvent, int *types, int size) {
    for (int i = 0; i < size; i++)
        if (xEvent->type == types[i])
            return True;

    return False;
}

std::shared_ptr<WindowState> WindowManagerX::getWindowState() {
    std::shared_ptr<WindowStateBuilder> builder(new DefaultWindowStateBuilder());

    XEvent xEvent;

    while (XCheckIfEvent(display, &xEvent, &WindowManagerX::selectWindowEventsPredicate, 0)) {
        switch (xEvent.type) {
            case FocusIn:
                builder->setGotFocus(true);

                break;
            case FocusOut:
                builder->setLostFocus(true);

                break;
            case ClientMessage:
                if (xEvent.xclient.message_type == wmProtocols) {
                    for (int i = 0; i < 5; i++) {
                        if (xEvent.xclient.data.l[i] == wmDeleteWindow)
                            builder->setClosing(true);
                    }
                }
        }
    }

    std::vector<int> position = getPosition();
    std::vector<uint> size = getSize();
    int state = getGeometryState();
    int maximizationState = getMaximizationState();

    if (position[0] != lastX || position[1] != lastY)
        builder->setMoved(true);

    if (size[0] != lastWidth || size[1] != lastHeight)
        builder->setResized(true);

    if (state != lastState) {
        switch (state) {
            case NORMAL:
                builder->setWindowed(true);

                break;
            case ICONIFIED:
                builder->setIconified(true);

                break;
            case HIDDEN_TO_TRAY:
                builder->setHiddenToTray(true);
                break;
        }
    }

    if (maximizationState != lastMaximizationState && maximizationState == MAXIMIZED_BOTH)
        builder->setMaximized(true);

    lastX = position[0];
    lastY = position[1];

    lastWidth = size[0];
    lastHeight = size[1];

    lastState = state;
    lastMaximizationState = maximizationState;

    return builder->build();
}

Bool WindowManagerX::selectWindowEventsPredicate(Display *display, XEvent *xEvent, XPointer arg) {
    int types[] = {FocusIn, FocusOut};

    return selectEventsPredicate(xEvent, types, 2) || xEvent->xclient.message_type == wmProtocols;
}

WindowManagerX::~WindowManagerX() {
    destroy();
}

WindowManagerX::PropertyData WindowManagerX::getProperty(const char* propertyName, Window window) const {
    Atom property, returnedProperty;

    int returnedActualFormat;

    ulong returnedNumberOfItems;
    ulong returnedBytesToRead;

    unsigned char* returnedData;

    property = XInternAtom(display, propertyName, False);

    XGetWindowProperty(display, window, property, 0, LONG_MAX, False,
                       AnyPropertyType, &returnedProperty, &returnedActualFormat,
                       &returnedNumberOfItems, &returnedBytesToRead, &returnedData);

    return PropertyData(returnedData, returnedNumberOfItems);
}

void WindowManagerX::sendEvent(int type, const char* messageTypeAtomName, int format, long *data, long eventMask,
                               Window from, Window to) {
    XEvent event;
    std::memset(&event, 0, sizeof(event));
    event.type = type;
    event.xclient.window = from;
    event.xclient.message_type = XInternAtom(display, messageTypeAtomName, False);
    event.xclient.format = format;

    for (uint i = 0; i < 5; i++)
        event.xclient.data.l[i] = data[i];

    XSendEvent(display, to, False, eventMask, &event);
}

void WindowManagerX::setWindowBounds(int x, int y, uint width, uint height, bool setCoordinates, bool setSize) {
    if (setCoordinates || setSize) {
        long data[5];

        data[0] = 0;

        if (setCoordinates) {
            data[0] |= 1UL << 8; //x
            data[0] |= 1UL << 9; //y
            data[1] = x;
            data[2] = y;
        }

        if (setSize) {
            data[0] |= 1UL << 10; //width
            data[0] |= 1UL << 11; //height
            data[3] = width;
            data[4] = height;
        }

        data[0] |= 1UL << 14; //pager (ahaha)

        sendEvent(ClientMessage, "_NET_MOVERESIZE_WINDOW", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
                  window, rootWindow);
    }
}

void
WindowManagerX::setSizeHints(uint minimumWidth, uint minimumHeight, uint maximumWidth, uint maximumHeight, uint ratioX,
                             uint ratioY, bool setMinimumSize, bool setMaximumSize, bool setRatio) {
    if (setMinimumSize || setMaximumSize || setRatio) {
            long hints = 0;

            XSizeHints* xOldSizeHints = XAllocSizeHints();

            long stab;
            XGetWMNormalHints(display, window, xOldSizeHints, &stab);

            /*
             * The following logic:
             * if setX then
                 * check if X != 0 then set
                 * else reset (do not add flag)
             * else
                 * check if oldX != 0 then set
                 * else reset (do not add flag)*/

            if (setRatio) {
                if (ratioX) {
                    xSizeHints->min_aspect.x = ratioX;
                    xSizeHints->min_aspect.y = ratioY;

                    xSizeHints->max_aspect.x = ratioX;
                    xSizeHints->max_aspect.y = ratioY;

                    hints |= PAspect;
                }
            } else {
                if (xOldSizeHints->min_aspect.x) {
                    xSizeHints->min_aspect.x = xOldSizeHints->min_aspect.x;
                    xSizeHints->min_aspect.y = xOldSizeHints->min_aspect.y;

                    xSizeHints->max_aspect.x = xOldSizeHints->max_aspect.x;
                    xSizeHints->max_aspect.y = xOldSizeHints->max_aspect.y;

                    hints |= PAspect;
                }
            }

            if (setMinimumSize) {
                if (minimumWidth) {
                    xSizeHints->min_width = minimumWidth;
                    xSizeHints->min_height = minimumHeight;

                    hints |= PMinSize;
                }
            } else {
                if (xOldSizeHints->min_width) {
                    xSizeHints->min_width = xOldSizeHints->min_width;
                    xSizeHints->min_height = xOldSizeHints->min_height;

                    hints |= PMinSize;
                }
            }

            if (setMaximumSize) {
                if (maximumWidth) {
                    xSizeHints->max_width = maximumWidth;
                    xSizeHints->max_height = maximumHeight;

                    hints |= PMaxSize;
                }
            } else {
                if (xOldSizeHints->max_width) {
                    xSizeHints->max_width = xOldSizeHints->max_width;
                    xSizeHints->max_height = xOldSizeHints->max_height;

                    hints |= PMaxSize;
                }
            }

            xSizeHints->flags = hints;
            XSetWMNormalHints(display, window, xSizeHints);
            XFree(xOldSizeHints);
            XFlush(display);
        }
}

void WindowManagerX::setMaximized(bool mode, Atom *atoms, int count) {
    long data[5];

    std::fill(data, data + 5, 0);

    data[0] = mode; //add - 1, remove - 0

    for (int i = 0; i < count; i++)
        data[1 + i] = atoms[i];

    sendEvent(ClientMessage, "_NET_WM_STATE", 32, data,  SubstructureRedirectMask
                                                         | SubstructureNotifyMask, window, rootWindow);
}

bool WindowManagerX::find(long needle, const PropertyData &haystack) const {
    for (int i = 0; i < haystack.numberOfItems; i++) {
        if (((long*)(haystack.data))[i] == needle)
            return true;
    }

    return false;
}

DMouseButton WindowManagerX::toDMouseButton(int xButton) const {
    switch (xButton) {
        case DEFAULT_LEFT_BUTTON:
            return Mouse::LEFT;
        case DEFAULT_MIDDLE_BUTTON:
            return Mouse::MIDDLE;
        case DEFAULT_RIGHT_BUTTON:
            return Mouse::RIGHT;
        default:
            return xButton;
    }
}

shared_ptr<Key> WindowManagerX::toDKey(XEvent *xEvent) const {
    DKeyCode dKeyCode = xKeyboardConverter->convertXKeyCodeToDKeyCode(xEvent);
    std::string keySymbol = xKeyboardConverter->convertXKeyCodeToSymbol(xEvent);

    return std::make_shared<DKey>(dKeyCode, keySymbol);
}