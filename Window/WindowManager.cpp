//
// Created by wcobalt on 16.09.18.
//

#include <memory>

#include "WindowManager.h"
#include "WindowAccessor.h"
#include "../Events/EventsData.h"

using std::shared_ptr;
using namespace dengine::events;
using namespace dengine::window;

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