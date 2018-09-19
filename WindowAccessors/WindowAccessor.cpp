//
// Created by wcobalt on 15.09.18.
//
//@todo dynamic WindowAccessor linking
#include "WindowAccessor.h"

void WindowAccessor::setEventsManager(EventsManager *eventsManager) {
    this->eventsManager = eventsManager;
}

EventsManager* WindowAccessor::getEventsManager() {
    return eventsManager;
}