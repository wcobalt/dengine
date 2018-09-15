#include <vector>
#include <map>

//
// Created by wcobalt on 15.09.18.
//

#include "EventManager.h"

EventHandler* EventManager::getFirstEventHandler(unsigned int eventType) {
    return eventsHandlers.find(eventType)->second;
}

std::vector<EventHandler*> EventManager::getEventHandlers(unsigned int eventType) {
    std::vector<EventHandler*> handlers;

    auto pairOfIterators = eventsHandlers.equal_range(eventType);

    for (auto i = pairOfIterators.first; i != pairOfIterators.second; i++) {
        handlers.push_back(i->second);
    }

    return handlers;
}

void EventManager::setEventHandler(unsigned int eventType, EventHandler* eventHandler) {
    eventsHandlers.insert(std::pair<unsigned int, EventHandler*>(eventType, eventHandler));
}