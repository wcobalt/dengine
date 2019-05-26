//
// Created by wcobalt on 23.05.19.
//

#include <unordered_set>

#ifndef DENGINE_DEFAULTMOUSESTATE_H
#define DENGINE_DEFAULTMOUSESTATE_H

#include "MouseState.h"

namespace dengine::events {
    class DefaultMouseState : public MouseState {
    private:
        std::unordered_set<int> pressedButtons;
        std::unordered_set<int> releasedButtons;

        int mouseWheelDirection;

        int rootX, rootY,
            windowX, windowY;
    public:
        DefaultMouseState(const std::unordered_set<int>& pressedButtons,
                          const std::unordered_set<int>& releasedButtons,
                          int mouseWheelDirection, int rootX, int rootY, int windowX, int windowY);

        bool isButtonPressed(int button) const;

        bool isButtonReleased(int button) const;

        int getMouseWheelDirection() const;

        std::vector<int> getRootMousePosition() const;

        std::vector<int> getWindowMousePosition() const;
    };
}

#endif //DENGINE_DEFAULTMOUSESTATE_H
