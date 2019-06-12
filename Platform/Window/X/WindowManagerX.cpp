//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <X11/Xatom.h>
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
#include "Exceptions/CouldNotOpenXDisplayException.h"
#include "Exceptions/NoSuitableXVisualInfoException.h"
#include "Exceptions/UnableToCreateGLXContextException.h"
#include "Exceptions/UnableToAttachGLXContextToWindow.h"
#include "Exceptions/TraySpecificationIsNotSupportedException.h"

using std::shared_ptr;
using std::vector;
using std::string;

using namespace dengine::events;
using namespace dengine::platform::window;
using namespace dengine::platform::window::x;
using namespace dengine::platform::window::x::exceptions;

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
                              Button4MotionMask | Button5MotionMask | ButtonMotionMask;

            XSetWindowAttributes xSetWindowAttributes;

            xSetWindowAttributes.colormap = colorMap;
            xSetWindowAttributes.event_mask = eventsMask;
            xSetWindowAttributes.background_pixel = XBlackPixel(display, DEFAULT_SCREEN);

            window = XCreateWindow(display, rootWindow, x, y, width, height, DEFAULT_WINDOW_DEPTH, visualInfo->depth,
                                   InputOutput, visualInfo->visual, CWColormap | CWEventMask | CWBackPixel, &xSetWindowAttributes);

            xSizeHints = XAllocSizeHints();

            setWindowPosition(x, y);

            setWindowTitle(title);

            setWindowSize(width, height);

            setCursorVisible(true);

            setDecorated(true);

            glXContext = glXCreateContext(display, visualInfo, nullptr, GL_TRUE);

            if (glXContext) {
                result = glXMakeCurrent(display, window, glXContext);

                if (result) {
                    Atom wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", false);

                    XSetWMProtocols(display, window, &wmDeleteWindow, 1);
                } else
                    throw UnableToAttachGLXContextToWindow();
            } else
                throw UnableToCreateGLXContextException();
        } else
            throw NoSuitableXVisualInfoException();
    } else
        throw CouldNotOpenXDisplayException();
}
//@todo blinking problem
void WindowManagerX::setVisible(bool isVisible) {
    if (isVisible)
        XMapWindow(display, window);
    else
        XUnmapWindow(display, window);

    XFlush(display);
}

void WindowManagerX::setDecorated(bool isDecorated) {
    vector<int> position = getWindowPosition();

    Atom type = XInternAtom(display,"_NET_WM_WINDOW_TYPE", False);
    Atom value = isDecorated?XInternAtom(display,"_NET_WM_WINDOW_TYPE_NORMAL", False):
                             XInternAtom(display,"_NET_WM_WINDOW_TYPE_SPLASH", False);

    XChangeProperty(display, window, type, XA_ATOM, 32, PropModeReplace, (unsigned char*)&value, 1);

    setWindowPosition(position[0], position[1]);

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

void WindowManagerX::setWindowPosition(int x, int y) {
    vector<uint> size = getWindowSize();

    setWindowBounds(x, y, size[0], size[1]);

    lastX = x;
    lastY = y;

    XFlush(display);
}

void WindowManagerX::setWindowSize(uint width, uint height) {
    vector<int> position = getWindowPosition();

    setWindowBounds(position[0], position[1], width, height);

    lastWidth = width;
    lastHeight = height;

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
    vector<uint> min = getMinimumSize(), max = getMaximumSize();

    setSizeHints(max[0], max[1], min[0], min[1], ratioX, ratioY);
}

void WindowManagerX::setTrayIcon(const long *buffer, int length) {

}

void WindowManagerX::setTrayName(const string &name) {

}

void WindowManagerX::sendNotification(const string &message) {

}

void WindowManagerX::setWindowTitle(const string& title) {
    Atom wmName = XInternAtom(display, "_NET_WM_NAME", False);
    Atom utf8String = XInternAtom(display, "UTF8_STRING", False);

    XChangeProperty(display, window, wmName, utf8String, 8, PropModeReplace, (const unsigned char*)(title.c_str()), (int)title.size());

    XFlush(display);
}

void WindowManagerX::setMinimumSize(uint minimumWidth, uint minimumHeight) {
    vector<uint> ratio = getRatio(), max = getMaximumSize();

    setSizeHints(max[0], max[1], minimumWidth, minimumHeight, ratio[0], ratio[1]);
}

void WindowManagerX::setMaximumSize(uint maximumWidth, uint maximumHeight) {
    vector<uint> ratio = getRatio(), min = getMinimumSize();

    setSizeHints(maximumWidth, maximumHeight, min[0], min[1], ratio[0], ratio[1]);
}

void WindowManagerX::setWindowGeometryState(WindowGeometryState windowGeometryState) {
    long data[5];

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    switch (windowGeometryState) {
        case NORMAL: {
            //state (! - may exist simultaneously with this property, so it needs to clear these properties):
            //maximized_h: false ! clearing by setMaximized*
            //maximized_v: false ! *
            //minimized: false
            //fullscreen: false ! by setFullscreen

            setFullscreenEnabled(false); //netwmfullscreen state and wmnormalstate may be simultaniiously so here
                                         //i remove fullscreen state
            setMaximized(false); //wmnormalstate and netwmmaximized_verthorz may be simultaneously so here
                                 //i remove both maximized

            setNormalStateEnabled(true);

            break;
        }

        case MAXIMIZED_HORIZONTAL: {
            //state (! - may exist simultaneously with this property, so it needs to clear these properties):
            //maximized_h: true
            //maximized_v: false ! by setWinGeo(NORMAL)*
            //minimized: false ! by *
            //fullscreen: false ! by setFull(false)

            setFullscreenEnabled(false);//netwmfullscreen state and wmnormalstate may exist simultaneously so here
                                        //i remove fullscreen state
            setWindowGeometryState(NORMAL);//wmiconicstate and netwmmaximized_verthorz may exist simultaneously so here
                                           //i remove iconic state if it is

            data[0] = 1; //add
            data[1] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);

            sendEvent(ClientMessage, "_NET_WM_STATE", 32, data,  SubstructureRedirectMask | SubstructureNotifyMask,
                      window,
                      rootWindow);

            break;
        }

        case MAXIMIZED_VERTICAL: {
            //state (! - may exist simultaneously with this property, so it needs to clear these properties):
            //maximized_h: false ! by setGeo(NORMAL)*
            //maximized_v: true
            //minimized: false ! by *
            //fullscreen: false ! by setFull(false)

            setFullscreenEnabled(false);
            setWindowGeometryState(NORMAL);

            data[0] = 1; //add
            data[1] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

            sendEvent(ClientMessage, "_NET_WM_STATE", 32, data,  SubstructureRedirectMask | SubstructureNotifyMask,
                      window,
                      rootWindow);

            break;
        }

        case MAXIMIZED_BOTH: {
            //state (! - may exist simultaneously with this property, so it needs to clear these properties):
            //maximized_h: true
            //maximized_v: true
            //minimized: false ! by setGeo(NORMAL)
            //fullscreen: false ! by setFull(false)

            setFullscreenEnabled(false);
            setWindowGeometryState(NORMAL);

            setMaximized(true);

            break;
        }

        case MINIMIZED: {
            //state (! - may exist simultaneously with this property, so it needs to clear these properties):
            //maximized_h: as is - so NO RESETTING
            //maximized_v: as is - so NO RESETTING
            //minimized: true
            //fullscreen: false ! by setFull(false)

            setFullscreenEnabled(false);

            data[0] = IconicState;

            sendEvent(ClientMessage, "WM_CHANGE_STATE", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
                      window,
                      rootWindow);

            break;
        }

        case FULLSCREEN: {
            //state (! - may exist simultaneously with this property, so it needs to clear these properties):
            //maximized_h: as is - so NO RESETTING
            //maximized_v: as is - so NO RESETTING
            //minimized: false ! by setNormalState(true) (no setGeo(NORMAL) because it resets max_vh)
            //fullscreen: true

            setNormalStateEnabled(true);
            setFullscreenEnabled(true);

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
                sendEvent(ClientMessage, "_NET_SYSTEM_TRAY_OPCODE", 32, data, NoEventMask, 0x1d6, 0x1d6);
            else
                throw TraySpecificationIsNotSupportedException();

            break;
        }
    }

    XFlush(display);
}

void WindowManagerX::centerWindow() {
    vector<uint> resolution = getScreenResolution();
    vector<uint> size = getWindowSize();

    int x = lastX, y = lastY;

    setWindowPosition((resolution[0] - size[0]) / 2, (resolution[1] - size[1]) / 2);

    //centering should not change last coordinates
    lastX = x;
    lastY = y;
}

void WindowManagerX::destroyWindow() {
    XDestroyWindow(display, window);

    XFree(visualInfo);
    XFree(xSizeHints);

    XCloseDisplay(display);
}

std::vector<uint> WindowManagerX::getScreenResolution() {
    vector<uint> result;

    result.emplace_back(XDisplayWidth(display, DEFAULT_SCREEN));
    result.emplace_back(XDisplayHeight(display, DEFAULT_SCREEN));

    return result;
}

/*bool WindowManagerX::isVisible() const {
    PropertyData propertyData = getProperty("_NET_WM_STATE", window);

    Atom hidden = XInternAtom(display, "_NET_WM_STATE_HIDDEN", False);

    for (int i = 0; i < propertyData.numberOfItems; i++) {
        if (((long*)(propertyData.data))[i] == hidden) return false;
    }

    return true;
}*/

bool WindowManagerX::isDecorated() const {
    return mIsDecorated;
}

bool WindowManagerX::isCursorVisible() const {
    return mIsCursorVisible;
}

vector<int> WindowManagerX::getWindowPosition() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    int x, y;

    Window w;

    XTranslateCoordinates(display, window, rootWindow,
            xWindowAttributes.x, xWindowAttributes.y, &x, &y, &w);

    vector<int> vec;

    vec.emplace_back(x - (uint)xWindowAttributes.x);
    vec.emplace_back(y - (uint)xWindowAttributes.y);

    return vec;
}

vector<int> WindowManagerX::getClientAreaPosition() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    vector<int> vec;

    vec.emplace_back((uint)xWindowAttributes.x);
    vec.emplace_back((uint)xWindowAttributes.y);

    return vec;
}

vector<uint> WindowManagerX::getWindowSize() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    vector<uint> vec;

    vec.emplace_back((uint)xWindowAttributes.width);
    vec.emplace_back((uint)xWindowAttributes.height);

    return vec;
}

std::vector<uint> WindowManagerX::getRatio() const {
    XSizeHints xSizeHints = {};

    XGetNormalHints(display, window, &xSizeHints);

    vector<uint> vec;

    vec.emplace_back((uint)xSizeHints.min_aspect.x);
    vec.emplace_back((uint)xSizeHints.min_aspect.y);

    return vec;
}

const std::string& WindowManagerX::getWindowTitle() const {
    return title;
}

vector<uint> WindowManagerX::getMinimumSize() const {
    XSizeHints xSizeHints = {};

    XGetNormalHints(display, window, &xSizeHints);

    vector<uint> vec;

    vec.emplace_back((uint)xSizeHints.min_width);
    vec.emplace_back((uint)xSizeHints.min_height);

    return vec;
}

vector<uint> WindowManagerX::getMaximumSize() const {
    XSizeHints xSizeHints = {};

    XGetNormalHints(display, window, &xSizeHints);

    vector<uint> vec;

    vec.emplace_back((uint)xSizeHints.max_width);
    vec.emplace_back((uint)xSizeHints.max_height);

    return vec;
}

WindowGeometryState WindowManagerX::getWindowGeometryState() const {
    //first tray then iconify and withdrawn then fullscreen then max_both, max_h, max_v, normal
    PropertyData result = getProperty("WM_STATE", window);

    for (int i = 0; i < result.numberOfItems; i++) {
        std::cout << ((long*)(result.data))[i];
    }
}

//@todo logging
//@todo tests
/*shared_ptr<const EventsData> WindowManagerX::checkEvents() {
    //@todo do events' masks is configured out of engine
    shared_ptr<EventsData> eventsData(new EventsData());

    while(XEventsQueued(display, QueuedAlready)) {
        XEvent xEvent;

        XNextEvent(display, &xEvent);

        switch(xEvent.type) {
            case KeyPress:
                eventsData->addPressedKey(xEvent.xkey.keycode);
                break;
            case KeyRelease:
                eventsData->addReleasedKey(xEvent.xkey.keycode);
                break;
            case ButtonPress:
                switch (xEvent.xbutton.button) {
                    case Button4:
                        eventsData->setMouseWheelDirection(1);
                        break;
                    case Button5:
                        eventsData->setMouseWheelDirection(-1);
                        break;
                    default:
                        eventsData->addPressedButton(xEvent.xbutton.button);
                }
                break;
            case ButtonRelease:
                eventsData->addReleasedButton(xEvent.xbutton.button);
                break;
            case ClientMessage:
                if(xEvent.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", false) &&
                   xEvent.xclient.data.l[0] == wmDeleteWindow) {
                    eventsData->setWindowClosing(true);
                }
        }
    }

    if(!eventsData->isWindowClosing()) {
        vector<uint> currentSize = getWindowSize();

        if(currentSize[0] != lastWidth || currentSize[1] != lastHeight) {
            eventsData->setWindowResized(true);

            lastWidth = currentSize[0];
            lastHeight = currentSize[1];
        }

        PropertyData focusState = getProperty("_NET_ACTIVE_WINDOW", 0, LONG_MAX, rootWindow);

        long activeWindowID = ((long*)(focusState.data))[0];

        bool currentFocusState = (activeWindowID == window);

        eventsData->setWindowFocused(currentFocusState);

        PropertyData windowState = getProperty("_NET_WM_STATE", 0, LONG_MAX, window);

        bool maximizedVert, maximizedHorz;

        maximizedVert = maximizedHorz = false;

        for(int i = 0; i < windowState.numberOfItems; i++) {
            long atom = ((long*) (windowState.data))[i];

            if(atom == XInternAtom(display, "_NET_WM_STATE_HIDDEN", false)) {
                eventsData->setWindowMinimized(true);
            } else if(atom == XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", false)) {
                maximizedHorz = true;
            } else if(atom == XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", false)) {
                maximizedVert = true;
            }
        }

        if(maximizedHorz && maximizedVert) eventsData->setWindowMaximized(true);
        else if(!maximizedHorz && !maximizedVert &&
                 !eventsData->isWindowMinimized())
            eventsData->setWindowWindowed(true);//!

        Window childWindow, rootWindow;

        uint mask;

        int rootMouseX, rootMouseY, windowMouseX, windowMouseY;

        XQueryPointer(display, window, &rootWindow, &childWindow, &rootMouseX,
                      &rootMouseY, &windowMouseX, &windowMouseY, &mask);

        shared_ptr<MousePosition> mousePosition(new MousePosition(rootMouseX, rootMouseY, windowMouseX, windowMouseY));

        eventsData->setMousePosition(mousePosition);
    }

    return eventsData;
}*/

std::shared_ptr<dengine::events::MouseState> WindowManagerX::getMouseState() const {
    return nullptr;
}

std::shared_ptr<dengine::events::KeyboardState> WindowManagerX::getKeyboardState() const {
    return nullptr;
}

std::shared_ptr<dengine::events::WindowState> WindowManagerX::getWindowState() const {
    return nullptr;
}


WindowManagerX::~WindowManagerX() {
    destroyWindow();
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

void WindowManagerX::setWindowBounds(int x, int y, uint width, uint height) {
    long data[5];

    data[0] = 0;

    data[0] |= 1UL << 8; //x
    data[0] |= 1UL << 9; //y
    data[0] |= 1UL << 10; //width
    data[0] |= 1UL << 11; //height

    data[0] |= 1UL << 14; //pager (ahaha)

    data[1] = x;
    data[2] = y;
    data[3] = width;
    data[4] = height;

    sendEvent(ClientMessage, "_NET_MOVERESIZE_WINDOW", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
            window, rootWindow);
}

void WindowManagerX::setSizeHints(uint maximumWidth, uint maximumHeight, uint minimumWidth, uint minimumHeight,
                                  uint ratioX, uint ratioY) {
    xSizeHints->flags = PAspect | PMaxSize | PMinSize;

    xSizeHints->min_aspect.x = ratioX;
    xSizeHints->min_aspect.y = ratioY;

    xSizeHints->max_aspect.x = ratioX;
    xSizeHints->max_aspect.y = ratioY;

    xSizeHints->min_width = minimumWidth;
    xSizeHints->min_height = minimumHeight;

    xSizeHints->max_width = maximumWidth;
    xSizeHints->max_height = maximumHeight;

    XSetWMNormalHints(display, window, xSizeHints);

    XFlush(display);
}

void WindowManagerX::setFullscreenEnabled(bool isEnabled) {
    long data[5];

    data[0] = isEnabled; //add - 1, remove - 0
    data[1] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;

    sendEvent(ClientMessage, "_NET_WM_STATE", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
              window,
              rootWindow);
}

void WindowManagerX::setMaximized(bool isMaximized) {
    long data[5];

    data[0] = isMaximized; //add
    data[1] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    data[2] = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    data[3] = 0;
    data[4] = 0;

    sendEvent(ClientMessage, "_NET_WM_STATE", 32, data,  SubstructureRedirectMask | SubstructureNotifyMask,
              window,
              rootWindow);
}

void WindowManagerX::setNormalStateEnabled(bool isEnabled) {
    long data[5];

    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;

    sendEvent(ClientMessage, "WM_CHANGE_STATE", 32, data, SubstructureRedirectMask | SubstructureNotifyMask,
              window,
              rootWindow);

    data[0] = NormalState;

    //hack for GNOME
    //https://stackoverflow.com/questions/30192347/how-to-restore-a-window-with-xlib

    data[0] = 1;
    data[1] = CurrentTime;

    sendEvent(ClientMessage, "_NET_ACTIVE_WINDOW", 32, data,  SubstructureRedirectMask | SubstructureNotifyMask,
              window,
              rootWindow);
}