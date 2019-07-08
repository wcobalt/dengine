//
// Created by wcobalt on 7/8/19.
//
#include <memory>
#include <set>

#include "DefaultMouseStateBuilder.h"
#include "DefaultMouseState.h"

using namespace dengine::events::mouse;

void DefaultMouseStateBuilder::addPressedButton(DMouseButton mouseButton) {
    pressedButtons.insert(mouseButton);
}

void DefaultMouseStateBuilder::addReleasedButton(DMouseButton mouseButton) {
    releasedButtons.insert(mouseButton);
}

void DefaultMouseStateBuilder::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void DefaultMouseStateBuilder::setWheelDirection(DWheelDirection wheelDirection) {
    this->mWheelDirection = wheelDirection;
}

std::shared_ptr<MouseState> DefaultMouseStateBuilder::build() const {
    std::shared_ptr<MouseState> result(new DefaultMouseState(pressedButtons, releasedButtons, mWheelDirection, x, y));

    return result;
}