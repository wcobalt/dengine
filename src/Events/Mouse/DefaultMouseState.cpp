//
// Created by wcobalt on 23.05.19.
//

#include <unordered_set>

#include "DefaultMouseState.h"

using namespace dengine::events::mouse;

DefaultMouseState::DefaultMouseState(const std::unordered_set<int>& pressedButtons,
                                     const std::unordered_set<int>& releasedButtons,
                                     int mouseWheelDirection, int windowX, int windowY):
                                     pressedButtons(pressedButtons), releasedButtons(releasedButtons),
                                     mouseWheelDirection(mouseWheelDirection),
                                     windowX(windowX), windowY(windowY) {}

bool DefaultMouseState::isButtonPressed(int button) const {
    auto it = pressedButtons.find(button);

    return it != pressedButtons.end();
}

bool DefaultMouseState::isButtonReleased(int button) const {
    auto it = releasedButtons.find(button);

    return it != releasedButtons.end();
}

std::vector<int> DefaultMouseState::getPosition() const {
    return {windowX, windowY};
}

int DefaultMouseState::getWheelDirection() const {
    return mouseWheelDirection;
}