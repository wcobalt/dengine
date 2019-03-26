//
// Created by wcobalt on 21.09.18.
//

#include "MousePosition.h"

using namespace dengine::events;

MousePosition::MousePosition(long rootMouseX, long rootMouseY, long windowMouseX, long windowMouseY) {
    this->rootMouseX = rootMouseX;
    this->rootMouseY = rootMouseY;
    this->windowMouseX = windowMouseX;
    this->windowMouseY = windowMouseY;
}

long MousePosition::getRootMouseX() const {
    return rootMouseX;
}

long MousePosition::getRootMouseY() const {
    return rootMouseY;
}

long MousePosition::getWindowMouseX() const {
    return windowMouseX;
}

long MousePosition::getWindowMouseY() const {
    return windowMouseY;
}