#include <GL/glx.h>
#include <X11/Xlib.h>
#include "../WindowAccessor.h"

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
    XEvent xEvent;

public:
    WindowAccessorX();
    int initialize(int, int, int, int, GLint[]);
};

#endif //DENGINE_WINDOWACCESSORX_H
