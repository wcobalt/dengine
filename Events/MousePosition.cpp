//
// Created by wcobalt on 21.09.18.
//

#include "MousePosition.h"

MousePosition::MousePosition() {
    rootMouseX = rootMouseY = windowMouseX = windowMouseY = 0;
}

MousePosition::MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY) {
    this->rootMouseX = rootMouseX;
    this->rootMouseY = rootMouseY;
    this->windowMouseX = windowMouseX;
    this->windowMouseY = windowMouseY;
}

int MousePosition::getRootMouseX() {
    return rootMouseX;
}

int MousePosition::getRootMouseY() {
    return rootMouseY;
}

int MousePosition::getWindowMouseX() {
    return windowMouseX;
}

int MousePosition::getWindowMouseY() {
    return windowMouseY;
}

void MousePosition::setRootMousePosition(int rootMouseX, int rootMouseY) {
    this->rootMouseX = rootMouseX;
    this->rootMouseY = rootMouseY;
}

void MousePosition::setWindowMousePosition(int windowMouseX, int windowMouseY) {
    this->windowMouseX = windowMouseX;
    this->windowMouseY = windowMouseY;
}