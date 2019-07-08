//
// Created by wcobalt on 22.05.19.
//

#include <vector>

#ifndef DENGINE_MOUSESTATE_H
#define DENGINE_MOUSESTATE_H

#include "../../DObject.h"
#include "Mouse.h"

namespace dengine::events::mouse {
    class MouseState : public DObject {
    public:
        virtual bool isButtonPressed(DMouseButton mouseButton) const = 0;

        virtual bool isButtonReleased(DMouseButton mouseButton) const = 0;

        virtual DWheelDirection getWheelDirection() const = 0;

        virtual std::vector<int> getPosition() const = 0;

        //@todo add method for all the pressed buttons getting (after release)
    };
}

#endif //DENGINE_MOUSESTATE_H
