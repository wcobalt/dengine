//
// Created by wcobalt on 21.09.18.
//

#include "../Geometry/vectors.h"
#include "MousePosition.h"

using namespace dengine::geometry;
using namespace dengine::events;

MousePosition::MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY) {
    this->rootMousePosition.x = rootMouseX;
    this->rootMousePosition.y = rootMouseY;

    this->windowMousePosition.x = windowMouseX;
    this->windowMousePosition.y = windowMouseY;
}

vec2i MousePosition::getRootMousePosition() const {
    return rootMousePosition;
}

vec2i MousePosition::getWindowMousePosition() const {
    return windowMousePosition;
}