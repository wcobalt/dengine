//
// Created by wcobalt on 22.05.19.
//
#include <set>

#ifndef DENGINE_KEYBOARDSTATE_H
#define DENGINE_KEYBOARDSTATE_H

#include "KeyCode.h"
#include "../../DObject.h"

namespace dengine::events::keyboard {
    class KeyboardState : public DObject {
    public:
        virtual bool isKeyPressed(DKeyCode key) const = 0;

        virtual bool isKeyReleased(DKeyCode key) const = 0;

        virtual bool isSymbolPressed(const std::string& symbol) const = 0;

        virtual bool isSymbolReleased(const std::string& symbol) const = 0;

        virtual std::string getCurrentKeyboardLayoutCode() const = 0;

        virtual std::string getCurrentKeyboardLayoutName() const = 0;
    };
}

#endif //DENGINE_KEYBOARDSTATE_H
