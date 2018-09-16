#include "EventsHandler.h"
#include <map>
#include <vector>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_EVENTSMANAGER_H
#define DENGINE_EVENTSMANAGER_H


class EventsManager {
private:
    std::multimap<unsigned int, EventsHandler*> eventsHandlers;
public:
    //deprecated
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

    const unsigned int MOUSE_EVENTS = 0;
    const unsigned int WINDOW_EVENTS = 1;
    const unsigned int KEY_EVENTS = 2;

    void setEventHandler(unsigned int, EventsHandler*);
    EventsHandler* getFirstEventHandler(unsigned int);
    std::vector<EventsHandler*> getEventHandlers(unsigned int);
};


#endif //DENGINE_EVENTSMANAGER_H
