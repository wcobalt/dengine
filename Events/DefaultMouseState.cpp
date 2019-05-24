//
// Created by wcobalt on 23.05.19.
//

#include "DefaultMouseState.h"

using namespace dengine::events;

DefaultMouseState::DefaultMouseState(const std::vector<int>& pressedButtons, const std::vector<int>& releasedButtons,
                                     int mouseWheelDirection, int rootX, int rootY, int windowX, int windowY):
                                     pressedButtons(pressedButtons), releasedButtons(releasedButtons),
                                     mouseWheelDirection(mouseWheelDirection), rootX(rootX), rootY(rootY),
                                     windowX(windowX), windowY(windowY) {}

bool DefaultMouseState::isButtonPressed(int mouseButton) const {
    //@todo implement
}

bool DefaultMouseState::isButtonReleased(int mouseButton) const {
    //@todo implement
}

std::vector<int> DefaultMouseState::getRootMousePosition() const {
    return {rootX, rootY};
}

std::vector<int> DefaultMouseState::getWindowMousePosition() const {
    return {windowX, windowY};
}

int DefaultMouseState::getMouseWheelDirection() const {
    return mouseWheelDirection;
}