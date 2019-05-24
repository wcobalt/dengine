//
// Created by wcobalt on 23.05.19.
//

#include "DefaultKeyboardState.h"

using namespace dengine::events;

DefaultKeyboardState::DefaultKeyboardState(const std::vector<int>& pressedKeys, const std::vector<int>& releasedKeys):
                                            pressedKeys(pressedKeys), releasedKeys(releasedKeys) {}

bool DefaultKeyboardState::isKeyPressed(int key) const {
    //@todo implement
}

bool DefaultKeyboardState::isKeyReleased(int key) const {
    //@todo implement
}