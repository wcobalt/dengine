//
// Created by wcobalt on 22.05.19.
//

#include <vector>

#ifndef DENGINE_MOUSESTATE_H
#define DENGINE_MOUSESTATE_H

#include "../../DObject.h"

namespace dengine::events {
    class MouseState : public DObject {
    public:
        virtual bool isButtonPressed(int mouseButton) const = 0;

        virtual bool isButtonReleased(int mouseButton) const = 0;

        virtual int getMouseWheelDirection() const = 0;

        virtual std::vector<int> getRootMousePosition() const = 0;

        virtual std::vector<int> getWindowMousePosition() const = 0;
    };
}

#endif //DENGINE_MOUSESTATE_H
