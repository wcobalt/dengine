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
        virtual void addPressedKey(std::shared_ptr<Key> key) = 0;

        virtual void addReleasedKey(std::shared_ptr<Key> key) = 0;

        virtual void setCurrentKeyboardLayoutCode(const std::string& layoutCode) = 0;

        virtual void setCurrentKeyboardLayoutName(const std::string& layoutName) = 0;

        virtual std::shared_ptr<KeyboardState> build() = 0;
    };
}


#endif //DENGINE_KEYBOARDSTATEBUILDER_H
