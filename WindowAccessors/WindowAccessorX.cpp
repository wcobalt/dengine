//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include "WindowAccessorX.h"
#include <iostream>
#include <string>

//X11 windowAccessor

WindowAccessorX::WindowAccessorX() = default;

int WindowAccessorX::initialize(int x, int y, unsigned int width, unsigned int height, GLint attributes[], long eventMask, std::string title) {
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