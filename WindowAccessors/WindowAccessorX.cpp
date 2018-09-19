//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include "WindowAccessorX.h"
#include <iostream>
#include <string>
#include "../Events/EventsHandlers/EventsHandler.h"
#include "../Events/EventsHandlers/KeyEventsHandler.h"
#include "../Events/EventsHandlers/MouseEventsHandler.h"
#include "../Events/EventsHandlers/EventsHandler.h"

//X11 windowAccessor

WindowAccessorX::WindowAccessorX() = default;

int WindowAccessorX::initialize(int x, int y, unsigned int width, unsigned int height,
                                GLint attributes[], long eventMask, std::string title) {
    display = XOpenDisplay(NULL);

    rootWindow = DefaultRootWindow(display);

    xVisualInfo = glXChooseVisual(display, 0, attributes);

    colorMap = XCreateColormap(display, rootWindow, xVisualInfo->visual, AllocNone);

    xSetWindowAttributes.colormap = colorMap;
    xSetWindowAttributes.event_mask = eventMask;

    window = XCreateWindow(display, rootWindow, x, y, width, height, 0, xVisualInfo->depth,
                InputOutput, xVisualInfo->visual, CWColormap | CWEventMask, &xSetWindowAttributes);

    XMapWindow(display, window);
    XStoreName(display, window, title.data());

    glXContext = glXCreateContext(display, xVisualInfo, NULL, GL_TRUE);

    glXMakeCurrent(display, window, glXContext);

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

EventsData* WindowAccessorX::checkEvents() {
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
                switch(xEvent.xbutton.button) {
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
            case MotionNotify:
                eventsData->setMouseCoordinates(xEvent.xmotion.x, xEvent.xmotion.y);
                break;
                //@todo destroy window and create events


        }
        //@todo window state
        //@todo window focus on/off
        //@todo windowResizing by lastWidth and newWidth
    }

    return eventsData;
}