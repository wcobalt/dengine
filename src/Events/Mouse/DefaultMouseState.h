//
// Created by wcobalt on 23.05.19.
//

#include <set>

#ifndef DENGINE_DEFAULTMOUSESTATE_H
#define DENGINE_DEFAULTMOUSESTATE_H

#include "MouseState.h"
#include "Mouse.h"

namespace dengine {
    class DefaultMouseState : public MouseState {
    private:
        std::set<DMouseButton> pressedButtons;
        std::set<DMouseButton> releasedButtons;

        DWheelDirection mWheelDirection;

        int x, y;
    public:
        DefaultMouseState(std::set<DMouseButton> pressedButtons,
                          std::set<DMouseButton> releasedButtons,
                          int wheelDirection, int x, int y);

        bool isButtonPressed(DMouseButton button) const;

        bool isButtonReleased(DMouseButton button) const;

        DWheelDirection getWheelDirection() const;

        std::vector<int> getPosition() const;
    };
}

#endif //DENGINE_DEFAULTMOUSESTATE_H
