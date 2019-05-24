//
// Created by wcobalt on 23.05.19.
//

#include <vector>

#ifndef DENGINE_DEFAULTKEYBOARDSTATE_H
#define DENGINE_DEFAULTKEYBOARDSTATE_H

#include "KeyboardState.h"

namespace dengine::events {
    class DefaultKeyboardState : public KeyboardState {
    private:
        std::vector<int> pressedKeys;
        std::vector<int> releasedKeys;
    public:
        DefaultKeyboardState(const std::vector<int>& pressedKeys, const std::vector<int>& releasedKeys);

        bool isKeyPressed(int key) const;

        bool isKeyReleased(int key) const;
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATE_H
