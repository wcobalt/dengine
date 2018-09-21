//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include "WindowAccessorX.h"
#include <iostream>
#include <string>
#include <climits>

//X11 windowAccessor

WindowAccessorX::WindowAccessorX() = default;

int WindowAccessorX::initialize(int x, int y, unsigned int width,
                                unsigned int height, std::string title) {
    //@todo to settings of WindowAccessor
    GLint attributes[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None};

    long eventsMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                      Button1MotionMask | Button2MotionMask | Button3MotionMask |
                      Button4MotionMask | Button5MotionMask | ButtonMotionMask | ResizeRedirectMask;

    display = XOpenDisplay(NULL);

    rootWindow = DefaultRootWindow(display);

    xVisualInfo = glXChooseVisual(display, 0, attributes);

    colorMap = XCreateColormap(display, rootWindow, xVisualInfo->visual, AllocNone);

    xSetWindowAttributes.colormap = colorMap;
    xSetWindowAttributes.event_mask = eventsMask;

    window = XCreateWindow(display, rootWindow, x, y, width, height, 0, xVisualInfo->depth,
                InputOutput, xVisualInfo->visual, CWColormap | CWEventMask, &xSetWindowAttributes);

    XMapWindow(display, window);
    XStoreName(display, window, title.data());

    glXContext = glXCreateContext(display, xVisualInfo, NULL, GL_TRUE);

    glXMakeCurrent(display, window, glXContext);

    GetPropertyData focusState = getProperty("_NET_ACTIVE_WINDOW", 0, LONG_MAX, rootWindow);

    long activeWindowID = ((long*)(focusState.data))[0];

    lastFocusState = (activeWindowID == window);

    return 0;
}

void WindowAccessorX::setX(int x) {

}

void WindowAccessorX::setY(int y) {

}

int WindowAccessorX::getX() {

}

int WindowAccessorX::getY() {

}

void WindowAccessorX::setWidth(unsigned int width) {

}

void WindowAccessorX::setHeight(unsigned int height) {

}

unsigned int WindowAccessorX::getWidth() {

}

unsigned int WindowAccessorX::getHeight() {

}

void WindowAccessorX::setWindowTitle(std::string title) {

}

void WindowAccessorX::getWindowTitle() {

}

std::vector<int> WindowAccessorX::getMinimumSizes() {

}

std::vector<int> WindowAccessorX::getMaximumSizes() {

}

void WindowAccessorX::setMinimumSizes(int minimumWidth, int minimumHeight) {

}

void WindowAccessorX::setMaximumSizes(int maximumWidth, int maximumHeight) {

}

EventsData* WindowAccessorX::checkEvents() {
    //@todo do events' masks is configured out of engine
    EventsData* eventsData = new EventsData();

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
                //@todo destroy window and create events
            case FocusIn:
                eventsData->setWindowGotFocus(true);
                break;
            case FocusOut:
                eventsData->setWindowLostFocus(true);
                break;
            case ResizeRequest:
                eventsData->setWindowResized(true);
                break;

        }
    }

    GetPropertyData focusState = getProperty("_NET_ACTIVE_WINDOW", 0, LONG_MAX, rootWindow);

    long activeWindowID = ((long*)(focusState.data))[0];

    bool currentFocusState = (activeWindowID == window);

    if (lastFocusState != currentFocusState) {
        if(lastFocusState) eventsData->setWindowLostFocus(true);
        else eventsData->setWindowGotFocus(true);
    }

    lastFocusState = currentFocusState;

    GetPropertyData windowState;

    windowState = getProperty("_NET_WM_STATE", 0, LONG_MAX, window);

    bool maximizedVert, maximizedHorz;

    maximizedVert = maximizedHorz = false;

    for(int i = 0; i < windowState.numberOfItems; i++) {
        long atom = ((long*)(windowState.data))[i];

        if (atom == XInternAtom(display, "_NET_WM_STATE_HIDDEN", false)) {
            eventsData->setWindowMinimized(true);
        } else if (atom == XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", false)) {
            maximizedHorz = true;
        } else if (atom == XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", false)) {
            maximizedVert = true;
        }
    }

    if (maximizedHorz && maximizedVert) eventsData->setWindowMaximized(true);
    else if (!maximizedHorz && !maximizedVert &&
             !eventsData->isWindowMinimized()) eventsData->setWindowWindowed(true);

    Window childWindow, rootWindow;

    unsigned int mask;

    int rootMouseX, rootMouseY, windowMouseX, windowMouseY;

    XQueryPointer(display, window, &rootWindow, &childWindow, &rootMouseX,
                  &rootMouseY, &windowMouseX, &windowMouseY, &mask);

    MousePosition mousePosition(rootMouseX, rootMouseY, windowMouseX, windowMouseY);

    eventsData->setMousePosition(mousePosition);

    return eventsData;
}

GetPropertyData WindowAccessorX::getProperty(char* propertyName, long offset,
                                             long size, Window window) {
    Atom property, returnedProperty;

    int returnedActualFormat;

    unsigned long returnedNumberOfItems;
    unsigned long returnedBytesToRead;
    unsigned char* returnedData = {};

    property = XInternAtom(display, propertyName, false);

    XGetWindowProperty(display, window, property, offset, size, false,
                       AnyPropertyType, &returnedProperty, &returnedActualFormat,
                       &returnedNumberOfItems, &returnedBytesToRead, &returnedData);

    return {returnedData, returnedNumberOfItems};
}