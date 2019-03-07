#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>
#include <vector>
#include <memory>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H

#include "../Events/EventsData.h"

class WindowAccessor {
public:
    const int NOT_FIXED_SIZE = -1;
    //@todo borders
    //@todo add defualt constructors
    //@todo initalize vs constructor
    virtual int initialize(int x, int y, uint width,
                           uint height, const std::string& title) = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual std::vector<int> getPosition() = 0;
    virtual void setSize(uint width, uint height) = 0;
    virtual std::vector<uint> getSize() = 0;
    virtual void setWindowTitle(std::string& title) = 0;
    virtual const std::string& getWindowTitle() const = 0;
    virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;
    virtual std::vector<uint> getMaximumSize() const = 0;
    virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;
    virtual std::vector<uint> getMinimumSize() const = 0;
    virtual void setFullscreenEnabled(bool isEnabled) = 0;
    virtual bool isFullscreenEnabled() const = 0;
    virtual std::shared_ptr<const EventsData> checkEvents() = 0;
    virtual void destroy() = 0;
};


#endif //DENGINE_WINDOWACCESSOR_H
