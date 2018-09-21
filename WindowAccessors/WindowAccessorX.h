#include <GL/glx.h>
#include <X11/Xlib.h>
#include "WindowAccessor.h"
#include <string>
#include "../Events/EventsData.h"
//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSORX_H
#define DENGINE_WINDOWACCESSORX_H

struct GetPropertyData {
    unsigned char* data;
    unsigned long numberOfItems;
};

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

    bool lastFocusState;

    GetPropertyData getProperty(char* propertyName, long offset, long size, Window window);
public:
    WindowAccessorX();
    virtual int initialize(int x, int y, unsigned int width,
                           unsigned int height, std::string title);
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
    //@todo vector2i vector2f 3f 3i as structs add
    virtual void setMaximumSizes(int maximumWidth, int maximumHeight);
    virtual std::vector<int> getMaximumSizes();
    virtual void setMinimumSizes(int minimumWidth, int minimumHeight);
    virtual std::vector<int> getMinimumSizes();
    //@todo replace pointers to "clever" pointers
    virtual EventsData* checkEvents();
};

#endif //DENGINE_WINDOWACCESSORX_H
