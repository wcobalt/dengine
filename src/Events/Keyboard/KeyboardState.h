//
// Created by wcobalt on 22.05.19.
//
#include <set>

#ifndef DENGINE_KEYBOARDSTATE_H
#define DENGINE_KEYBOARDSTATE_H

#include "Keyboard.h"
#include "../../DObject.h"

namespace dengine {
    class Key;
}

namespace dengine {
    class KeyboardState : public DObject {
    public:
        virtual bool isKeyPressed(DKeyCode key) const = 0;

        virtual bool isKeyReleased(DKeyCode key) const = 0;

        virtual bool isSymbolPressed(std::string_view symbol) const = 0;

        virtual bool isSymbolReleased(std::string_view symbol) const = 0;

        virtual const std::string & getCurrentKeyboardLayoutCode() const = 0;

        virtual const std::string & getCurrentKeyboardLayoutName() const = 0;

        virtual const std::set<Key*> & getAllPressedKeys() const = 0;

        virtual const std::set<Key*> & getAllReleasedKeys() const = 0;
    };
}

#endif //DENGINE_KEYBOARDSTATE_H
