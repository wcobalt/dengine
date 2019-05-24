//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include <string>
#include <climits>
#include <thread>
#include <cstring>
#include <memory>
#include <vector>

#include "WindowAccessorX.h"
#include "../Events/MousePosition.h"
#include "../Events/EventsData.h"

using std::shared_ptr;
using std::vector;
using namespace dengine::window;
using namespace dengine::events;
using namespace dengine::geometry;

WindowAccessorX::WindowAccessorX(int x, int y, uint width,
                                uint height, const std::string& title):title(title) {
    //@todo to settings of WindowAccessor
    GLint attributes[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None};

    long eventsMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                      Button1MotionMask | Button2MotionMask | Button3MotionMask |
                      Button4MotionMask | Button5MotionMask | ButtonMotionMask;

    display = XOpenDisplay(NULL);

    rootWindow = DefaultRootWindow(display);

    xVisualInfo = glXChooseVisual(display, 0, attributes);

    colorMap = XCreateColormap(display, rootWindow, xVisualInfo->visual, AllocNone);

    xSetWindowAttributes.colormap = colorMap;
    xSetWindowAttributes.event_mask = eventsMask;

    window = XCreateWindow(display, rootWindow, x, y, width, height, 0, xVisualInfo->depth,
                InputOutput, xVisualInfo->visual, CWColormap | CWEventMask, &xSetWindowAttributes);

    XMapWindow(display, window);

    setWindowPosition(x, y);

    setWindowTitle(title);

    glXContext = glXCreateContext(display, xVisualInfo, NULL, GL_TRUE);

    glXMakeCurrent(display, window, glXContext);

    wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", false);

    XSetWMProtocols(display, window, &wmDeleteWindow, 1);

    lastWidth = width;
    lastHeight = height;
}

void WindowAccessorX::setVisible(bool isVisible) {
    if (isVisible)
        XMapWindow(display, window);
    else
        XUnmapWindow(display, window);
    //@todo implement

}

void WindowAccessorX::setDecorated(bool isDecorated) {
    //@todo implement
}

void WindowAccessorX::setCursorVisible(bool isVisible) {
    //@todo implement
}

void WindowAccessorX::setWindowPosition(int x, int y) {
    XMoveWindow(display, window, x, y);
    XFlush(display);
}

void WindowAccessorX::setSize(uint width, uint height) {
    XResizeWindow(display, window, width, height);
    XFlush(display);
}

void WindowAccessorX::setWindowTitle(const std::string& title) {
    XStoreName(display, window, title.c_str());
    XFlush(display);
}

void WindowAccessorX::setMinimumSize(uint minimumWidth, uint minimumHeight) {
    vector<uint> maximumSize = getMaximumSize();

    setMinimumAndMaximumSize(maximumSize[0], maximumSize[1], minimumWidth, minimumHeight);
}

void WindowAccessorX::setMaximumSize(uint maximumWidth, uint maximumHeight) {
    vector<uint> minimumSize = getMinimumSize();

    setMinimumAndMaximumSize(maximumWidth, maximumHeight, minimumSize[0], minimumSize[1]);
}

void WindowAccessorX::setFullscreenEnabled(bool isEnabled) {
    XEvent event;
    std::memset(&event, 0, sizeof(event));
    event.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
    event.xclient.format = 32;
    event.xclient.data.l[0] = isEnabled?1:0;
    event.xclient.data.l[1] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
    event.xclient.data.l[2] = 0;

    XSendEvent(display, rootWindow, False,
               SubstructureRedirectMask | SubstructureNotifyMask, &event);
}

bool WindowAccessorX::isVisible() const {
    //@todo implement
}

bool WindowAccessorX::isDecorated() const {
    //@todo implement
}

bool WindowAccessorX::isCursorVisible() const {
    //@todo implement
}

vector<int> WindowAccessorX::getWindowPosition() const {
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

vector<int> WindowAccessorX::getClientAreaPosition() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    vector<int> vec;

    vec.emplace_back((uint)xWindowAttributes.x);
    vec.emplace_back((uint)xWindowAttributes.y);

    return vec;
}

vector<uint> WindowAccessorX::getSize() const {
    XWindowAttributes xWindowAttributes;

    XGetWindowAttributes(display, window, &xWindowAttributes);

    vector<uint> vec;

    vec.emplace_back((uint)xWindowAttributes.width);
    vec.emplace_back((uint)xWindowAttributes.height);

    return vec;
}

const std::string& WindowAccessorX::getWindowTitle() const {
    return title;
}

vector<uint> WindowAccessorX::getMinimumSize() const {
    XSizeHints xSizeHints = {};

    XGetNormalHints(display, window, &xSizeHints);

    vector<uint> vec;

    vec.emplace_back((uint)xSizeHints.min_width);
    vec.emplace_back((uint)xSizeHints.min_height);

    return vec;
}

vector<uint> WindowAccessorX::getMaximumSize() const {
    XSizeHints xSizeHints = {};

    XGetNormalHints(display, window, &xSizeHints);

    vector<uint> vec;

    vec.emplace_back((uint)xSizeHints.max_width);
    vec.emplace_back((uint)xSizeHints.max_height);

    return vec;
}

void WindowAccessorX::setMinimumAndMaximumSize(uint maximumWidth, uint maximumHeight,
                                               uint minimumWidth, uint minimumHeight) {
        XSizeHints xSizeHints = {};

        xSizeHints.flags = PMaxSize | PMinSize;

        xSizeHints.max_width = maximumWidth;
        xSizeHints.max_height = maximumHeight;

        xSizeHints.min_width = minimumWidth;
        xSizeHints.min_height = minimumHeight;

        XSetWMNormalHints(display, window, &xSizeHints);
}

bool WindowAccessorX::isFullscreenEnabled() const {
    PropertyData data = getProperty("_NET_WM_STATE", 0, LONG_MAX, window);

    for(int i = 0; i < data.numberOfItems; i++) {
        if(((long*)(data.data))[i] == XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", false)) {
            return true;
        }
    }

    return false;
}

//@todo logging
//@todo tests
shared_ptr<const EventsData> WindowAccessorX::checkEvents() {
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
        vector<uint> currentSize = getSize();

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
}

WindowAccessorX::~WindowAccessorX() {
    destroy();
}

void WindowAccessorX::destroy() {
    XDestroyWindow(display, window);

    delete display;
    delete xVisualInfo;
}

PropertyData WindowAccessorX::getProperty(const char* propertyName, long offset,
                                             long size, Window window) const {
    Atom property, returnedProperty;

    int returnedActualFormat;

    ulong returnedNumberOfItems;
    ulong returnedBytesToRead;
    unsigned char* returnedData;

    property = XInternAtom(display, propertyName, false);

    delete[] propertyName;

    XGetWindowProperty(display, window, property, offset, size, false,
                         AnyPropertyType, &returnedProperty, &returnedActualFormat,
                         &returnedNumberOfItems, &returnedBytesToRead, &returnedData);

    return PropertyData(returnedData, returnedNumberOfItems);
}