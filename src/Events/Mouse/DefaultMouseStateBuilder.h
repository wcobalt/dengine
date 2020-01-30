//
// Created by wcobalt on 7/8/19.
//
#include <memory>
#include <set>

#ifndef DENGINE_DEFAULTMOUSEBUILDER_H
#define DENGINE_DEFAULTMOUSEBUILDER_H

#include "Mouse.h"
#include "MouseStateBuilder.h"

namespace dengine {
    class DefaultMouseStateBuilder : public MouseStateBuilder {
    private:
        std::set<DMouseButton> pressedButtons;
        std::set<DMouseButton> releasedButtons;

        DWheelDirection mWheelDirection;

        int x, y;
    public:
        void addPressedButton(DMouseButton mouseButton);

        void addReleasedButton(DMouseButton mouseButton);

        void setWheelDirection(DWheelDirection wheelDirection);

        void setPosition(int x, int y);

        std::unique_ptr<MouseState> build() const;
    };
}

#endif //DENGINE_DEFAULTMOUSEBUILDER_H
