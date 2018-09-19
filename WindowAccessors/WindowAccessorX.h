#include <GL/glx.h>
#include <X11/Xlib.h>
#include "WindowAccessor.h"
#include <string>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSORX_H
#define DENGINE_WINDOWACCESSORX_H

class WindowAccessorX : public WindowAccessor {
private:
    Display *display;
    Window rootWindow;
    XVisualInfo *xVisualInfo;
    Colormap colorMap;
    XSetWindowAttributes xSetWindowAttributes;
    Window window;
    GLXContext glXContext;
    XWindowAttributes xWindowAttributes;
public:
    WindowAccessorX();
    virtual int initialize(int x, int y, unsigned int width, unsigned int height,
                           GLint attributes[], long eventMask, std::string title);
    virtual void setX(int x);
    virtual void setY(int y);
    virtual int getX();
    virtual int getY();
    virtual void setWidth(unsigned int width);
    virtual void setHeight(unsigned int height);
    virtual unsigned int getWidth();
    virtual unsigned int getHeight();
    virtual void setWindowTitle(std::string title);
    virtual void getWindowTitle();
    virtual void checkEvents();
};

#endif //DENGINE_WINDOWACCESSORX_H
