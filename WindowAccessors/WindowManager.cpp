//
// Created by wcobalt on 16.09.18.
//

#include "WindowManager.h"

WindowManager::WindowManager(std::shared_ptr<WindowAccessor> windowAccessor) {
    this->windowAccessor = windowAccessor;//@todo hmm
}

std::shared_ptr<WindowAccessor> WindowManager::getWindowAccessor() {
    return windowAccessor;
}