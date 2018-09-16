#include <vector>
#include <map>

//
// Created by wcobalt on 15.09.18.
//

#include "EventsManager.h"

EventsHandler* EventsManager::getFirstEventHandler(unsigned int eventType) {
    return eventsHandlers.find(eventType)->second;
}

std::vector<EventsHandler*> EventsManager::getEventHandlers(unsigned int eventType) {
    std::vector<EventsHandler*> handlers;

    auto pairOfIterators = eventsHandlers.equal_range(eventType);

    for (auto i = pairOfIterators.first; i != pairOfIterators.second; i++) {
        handlers.push_back(i->second);
    }

    return handlers;
}

void EventsManager::setEventHandler(unsigned int eventType, EventsHandler* eventHandler) {
    eventsHandlers.insert(std::pair<unsigned int, EventsHandler*>(eventType, eventHandler));
}