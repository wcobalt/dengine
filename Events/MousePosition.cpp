//
// Created by wcobalt on 21.09.18.
//

#include "MousePosition.h"

MousePosition::MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY) {
    this->rootMouseX = rootMouseX;
    this->rootMouseY = rootMouseY;
    this->windowMouseX = windowMouseX;
    this->windowMouseY = windowMouseY;
}

int MousePosition::getRootMouseX() const {
    return rootMouseX;
}

int MousePosition::getRootMouseY() const {
    return rootMouseY;
}

int MousePosition::getWindowMouseX() const {
    return windowMouseX;
}

int MousePosition::getWindowMouseY() const {
    return windowMouseY;
}