//
// Created by wcobalt on 22.05.19.
//

#include <set>

#ifndef DENGINE_KEYBOARDSTATE_H
#define DENGINE_KEYBOARDSTATE_H

#include "../../DObject.h"

namespace dengine::events {
    class KeyboardState : public DObject {
    public:
        virtual bool isKeyPressed(int key) const = 0;

        virtual bool isKeyReleased(int key) const = 0;
    };
}

#endif //DENGINE_KEYBOARDSTATE_H
