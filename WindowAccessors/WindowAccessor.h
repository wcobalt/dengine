#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>
#include <vector>

//
// Created by wcobalt on 15.09.18.
//

#include "../Events/EventsData.h"

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H

class WindowAccessor {
public:
    const int NOT_FIXED_SIZE = -1;
    //@todo borders
    //@todo add defualt constructors
    //@todo initalize vs constructor
    virtual int initialize(int x, int y, unsigned int width,
                           unsigned int height, std::string& title) = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual std::vector<int> getPosition() = 0;
    virtual void setSize(unsigned int width, unsigned int height) = 0;
    virtual std::vector<unsigned int> getSize() = 0;
    virtual void setWindowTitle(std::string title) = 0;
    virtual const std::string& getWindowTitle() const = 0;
    virtual void setMaximumSize(int maximumWidth, int maximumHeight) = 0;
    virtual std::vector<int> getMaximumSize() const = 0;
    virtual void setMinimumSize(int minimumWidth, int minimumHeight) = 0;
    virtual std::vector<int> getMinimumSize() const = 0;
    virtual void setFullscreenEnabled(bool isEnabled) = 0;
    virtual bool isFullscreenEnabled() const = 0;
    virtual const EventsData& checkEvents() = 0;
    virtual void destroy() = 0;
};


#endif //DENGINE_WINDOWACCESSOR_H
