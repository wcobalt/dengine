//
// Created by wcobalt on 16.09.18.
//

#include "WindowManager.h"

using namespace dengine::windowaccessors;

WindowManager::WindowManager(std::shared_ptr<WindowAccessor> windowAccessor) {
    this->windowAccessor = windowAccessor;
}

std::shared_ptr<WindowAccessor> WindowManager::getWindowAccessor() {
    return windowAccessor;
}