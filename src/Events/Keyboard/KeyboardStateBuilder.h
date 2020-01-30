//
// Created by wcobalt on 22.08.19.
//

#include <string>

#ifndef DENGINE_KEYBOARDSTATEBUILDER_H
#define DENGINE_KEYBOARDSTATEBUILDER_H

namespace dengine {
    class Key;
    class KeyboardState;
}

namespace dengine {
    class KeyboardStateBuilder {
    public:
        virtual void addPressedKey(std::unique_ptr<Key> key) = 0;

        virtual void addReleasedKey(std::unique_ptr<Key> key) = 0;

        virtual void setCurrentKeyboardLayoutCode(std::string layoutCode) = 0;

        virtual void setCurrentKeyboardLayoutName(std::string layoutName) = 0;

        virtual std::unique_ptr<KeyboardState> build() = 0;
    };
}


#endif //DENGINE_KEYBOARDSTATEBUILDER_H
