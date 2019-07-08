//
// Created by wcobalt on 7/8/19.
//
#include <memory>

#ifndef DENGINE_MOUSESTATEBUILDER_H
#define DENGINE_MOUSESTATEBUILDER_H

#include "Mouse.h"

namespace dengine::events::mouse {
    class MouseState;
}

namespace dengine::events::mouse {
    class MouseStateBuilder {
    public:
        virtual void addPressedButton(DMouseButton mouseButton) = 0;

        virtual void addReleasedButton(DMouseButton mouseButton) = 0;

        virtual void setWheelDirection(DWheelDirection mouseButton) = 0;

        virtual void setPosition(int x, int y) = 0;

        virtual std::shared_ptr<MouseState> build() const = 0;
    };
}

#endif //DENGINE_MOUSESTATEBUILDER_H
