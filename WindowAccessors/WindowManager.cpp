//
// Created by wcobalt on 16.09.18.
//

#include "WindowManager.h"

WindowManager::WindowManager(WindowAccessor * windowAccessor) {
    this->windowAccessor = windowAccessor;
}

WindowAccessor* WindowManager::getWindowAccessor() {
    return windowAccessor;
}