#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>
#include "../Events/EventsManager.h"

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H


class WindowAccessor {
private:
    EventsManager* eventsManager;
public:
    //@todo borders
    virtual int initialize(int, int, unsigned int, unsigned int, GLint[], long, std::string) = 0;
    virtual void setX(int x) = 0;
    virtual void setY(int y) = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual void setWidth(unsigned int width) = 0;
    virtual void setHeight(unsigned int height) = 0;
    virtual unsigned int getWidth() = 0;
    virtual unsigned int getHeight() = 0;
    virtual void setWindowTitle(std::string title) = 0;
    virtual void getWindowTitle() = 0;
    void setEventsManager(EventsManager* eventsManager);
    EventsManager* getEventsManager();
    virtual void checkEvents() = 0;
};


#endif //DENGINE_WINDOWACCESSOR_H
