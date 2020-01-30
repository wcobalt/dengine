//
// Created by wcobalt on 23.05.19.
//

#include <set>

#include "DefaultMouseState.h"

using namespace dengine;

DefaultMouseState::DefaultMouseState(std::set<DMouseButton> pressedButtons,
                                     std::set<DMouseButton> releasedButtons,
                                     int wheelDirection, int x, int y):
                                     pressedButtons(std::move(pressedButtons)),
                                     releasedButtons(std::move(releasedButtons)),
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