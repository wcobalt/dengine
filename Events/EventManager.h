#include "EventHandler.h"
#include <map>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_EVENTMANAGER_H
#define DENGINE_EVENTMANAGER_H


class EventManager {
private:
    std::map<unsigned int, EventHandler> eventsHandlers;
public:
    const unsigned int EVENT_CLICK = 0;
    const unsigned int EVENT_LEFT_BUTTON_CLICK = 1;
    const unsigned int EVENT_RIGHT_BUTTON_CLICK = 2;
    const unsigned int EVENT_MIDDLE_BUTTON_CLICK = 3;
    const unsigned int EVENT_MOUSE_MOVE = 4;
    const unsigned int EVENT_MOUSE_OVER = 5;
    const unsigned int EVENT_MOUSE_OUT = 6;
    const unsigned int EVENT_WINDOW_OPEN = 7;
    const unsigned int EVENT_WINDOW_CLOSE = 8;
    const unsigned int EVENT_WINDOW_MINIMIZE = 9;
    const unsigned int EVENT_WINDOW_MAXIMIZE = 10;
    const unsigned int EVENT_WINDOW_WINDOWED = 11;
    const unsigned int EVENT_KEY_PRESS = 12;
    const unsigned int EVENT_KEY_RELEASE = 13;
    //@TODO king of consts needs more consts!!!

    void setEventHandler(unsigned int event, EventHandler eventHandler);
    EventHandler getEventHandler(unsigned int event);
};


#endif //DENGINE_EVENTMANAGER_H
