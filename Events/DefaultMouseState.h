//
// Created by wcobalt on 23.05.19.
//

#include <vector>

#ifndef DENGINE_DEFAULTMOUSESTATE_H
#define DENGINE_DEFAULTMOUSESTATE_H

#include "MouseState.h"

namespace dengine::events {
    class DefaultMouseState : public MouseState {
    private:
        std::vector<int> pressedButtons;
        std::vector<int> releasedButtons;

        int mouseWheelDirection;

        int rootX, rootY,
            windowX, windowY;
    public:
        DefaultMouseState(const std::vector<int>& pressedButtons, const std::vector<int>& releasedButtons,
                          int mouseWheelDirection, int rootX, int rootY, int windowX, int windowY);

        bool isButtonPressed(int mouseButton) const;

        bool isButtonReleased(int mouseButton) const;

        int getMouseWheelDirection() const;

        std::vector<int> getRootMousePosition() const;

        std::vector<int> getWindowMousePosition() const;
    };
}

#endif //DENGINE_DEFAULTMOUSESTATE_H
