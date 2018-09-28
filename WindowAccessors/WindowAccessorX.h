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

    Atom wmDeleteWindow;

    unsigned int lastWidth, lastHeight;

    GetPropertyData getProperty(char* propertyName, long offset, long size, Window window);
    void setMinimumAndMaximumSize(int maximumWidth, int maximumHeight, int minimumWidth, int minimumHeight);
public:
    WindowAccessorX();
    virtual int initialize(int x, int y, unsigned int width,
                           unsigned int height, std::string title);
    virtual void setPosition(int x, int y);
    virtual std::vector<int> getPosition();
    virtual void setSize(unsigned int width, unsigned int height);
    virtual std::vector<unsigned int> getSize();
    virtual void setWindowTitle(std::string title);
    virtual std::string getWindowTitle();
    virtual void setMaximumSize(int maximumWidth, int maximumHeight);
    virtual std::vector<int> getMaximumSize();
    virtual void setMinimumSize(int minimumWidth, int minimumHeight);
    virtual std::vector<int> getMinimumSize();
    virtual void setFullscreenEnabled(bool isEnabled);
    virtual bool isFullscreenEnabled();
    //@todo vector2i vector2f 3f 3i as structs add
    //@todo replace pointers to "smart" pointers
    virtual EventsData* checkEvents();
    virtual void destroy();
};

#endif //DENGINE_WINDOWACCESSORX_H
