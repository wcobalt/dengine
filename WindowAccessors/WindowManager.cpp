//
// Created by wcobalt on 16.09.18.
//

#include "WindowManager.h"

using namespace dengine::windowaccessors;

WindowManager::WindowManager(shared_ptr<WindowAccessor> windowAccessor) {
    this->windowAccessor = windowAccessor;
}

void WindowManager::checkEvents() {
    eventsData = windowAccessor->checkEvents();
}

shared_ptr<WindowAccessor> WindowManager::getWindowAccessor() {
    return windowAccessor;
}

shared_ptr<const EventsData> WindowManager::getEventsData() const {
    return eventsData;
}