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

struct PropertyData {
    unsigned char* data;
    ulong numberOfItems;
};

class WindowAccessorX : public WindowAccessor {
private:
    Display* display;
    Window rootWindow;
    XVisualInfo* xVisualInfo;
    Colormap colorMap;
    XSetWindowAttributes xSetWindowAttributes;
    Window window;
    GLXContext glXContext;
    XWindowAttributes xWindowAttributes;

    Atom wmDeleteWindow;

    unsigned int lastWidth, lastHeight;

    PropertyData getProperty(char* propertyName, long offset, long size, Window window) const;
    void setMinimumAndMaximumSize(uint maximumWidth, uint maximumHeight,
                                  uint minimumWidth, uint minimumHeight);
public:
    WindowAccessorX();
    int initialize(int x, int y, uint width,
                           uint height, const std::string& title);
    void setPosition(int x, int y);
    std::vector<int> getPosition();//@todo may be mark as const, getSize() too?
    void setSize(uint width, uint height);
    std::vector<uint> getSize();
    void setWindowTitle(std::string title);
    const std::string& getWindowTitle() const;
    void setMaximumSize(uint maximumWidth, uint maximumHeight);
    std::vector<uint> getMaximumSize() const;
    void setMinimumSize(uint minimumWidth, uint minimumHeight);
    std::vector<uint> getMinimumSize() const;
    void setFullscreenEnabled(bool isEnabled);
    bool isFullscreenEnabled() const;
    //@todo vector2i vector2f 3f 3i as classes add
    std::shared_ptr<const EventsData> checkEvents();
    void destroy();
};

#endif //DENGINE_WINDOWACCESSORX_H
