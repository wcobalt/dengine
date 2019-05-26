//
// Created by wcobalt on 23.05.19.
//

#include <unordered_set>

#ifndef DENGINE_DEFAULTKEYBOARDSTATE_H
#define DENGINE_DEFAULTKEYBOARDSTATE_H

#include "KeyboardState.h"

namespace dengine::events {
    class DefaultKeyboardState : public KeyboardState {
    private:
        std::unordered_set<int> pressedKeys;
        std::unordered_set<int> releasedKeys;
    public:
        DefaultKeyboardState(const std::unordered_set<int>& pressedKeys,
                             const std::unordered_set<int>& releasedKeys);

        bool isKeyPressed(int key) const;

        bool isKeyReleased(int key) const;
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATE_H
