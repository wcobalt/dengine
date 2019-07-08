//
// Created by wcobalt on 23.05.19.
//

#include <set>

#include "DefaultMouseState.h"

using namespace dengine::events::mouse;

DefaultMouseState::DefaultMouseState(const std::set<DMouseButton>& pressedButtons,
                                     const std::set<DMouseButton>& releasedButtons,
                                     int wheelDirection, int x, int y):
                                     pressedButtons(pressedButtons), releasedButtons(releasedButtons),
                                     mWheelDirection(wheelDirection),
                                     x(x), y(y) {}

bool DefaultMouseState::isButtonPressed(DMouseButton button) const {
    auto it = pressedButtons.find(button);

    return it != pressedButtons.end();
}

bool DefaultMouseState::isButtonReleased(DMouseButton button) const {
    auto it = releasedButtons.find(button);

    return it != releasedButtons.end();
}

DWheelDirection DefaultMouseState::getWheelDirection() const {
    return mWheelDirection;
}

std::vector<int> DefaultMouseState::getPosition() const {
    return {x, y};
}