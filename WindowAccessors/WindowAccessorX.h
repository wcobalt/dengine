#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSORX_H
#define DENGINE_WINDOWACCESSORX_H

#include "WindowAccessor.h"
#include "../Events/EventsData.h"

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

    GetPropertyData getProperty(char* propertyName, long offset, long size, Window window) const;
    void setMinimumAndMaximumSize(int maximumWidth, int maximumHeight, int minimumWidth, int minimumHeight);
public:
    WindowAccessorX();
    int initialize(int x, int y, unsigned int width,
                           unsigned int height, std::string& title);
    void setPosition(int x, int y);
    std::vector<int> getPosition();//@todo may be mark as const?
    void setSize(unsigned int width, unsigned int height);
    std::vector<unsigned int> getSize();//@todo may be mark as const?
    void setWindowTitle(std::string title);
    const std::string& getWindowTitle() const;
    void setMaximumSize(int maximumWidth, int maximumHeight);
    std::vector<int> getMaximumSize() const;
    void setMinimumSize(int minimumWidth, int minimumHeight);
    std::vector<int> getMinimumSize() const;
    void setFullscreenEnabled(bool isEnabled);
    bool isFullscreenEnabled() const;
    //@todo vector2i vector2f 3f 3i as structs add
    //@todo replace pointers to "smart" pointers
    const EventsData& checkEvents();
    void destroy();
};

#endif //DENGINE_WINDOWACCESSORX_H
