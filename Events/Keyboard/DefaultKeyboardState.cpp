//
// Created by wcobalt on 23.05.19.
//

#include <unordered_set>

#include "DefaultKeyboardState.h"

using namespace dengine::events;

DefaultKeyboardState::DefaultKeyboardState(const std::unordered_set<int>& pressedKeys,
                                            const std::unordered_set<int>& releasedKeys):
                                            pressedKeys(pressedKeys), releasedKeys(releasedKeys) {}

bool DefaultKeyboardState::isKeyPressed(int key) const {
    auto it = pressedKeys.find(key);

    return it != pressedKeys.end();
}

bool DefaultKeyboardState::isKeyReleased(int key) const {
    auto it = releasedKeys.find(key);

    return it != releasedKeys.end();
}