//
// Created by wcobalt on 22.08.19.
//
#include <string>
#include <set>
#include <memory>

#ifndef DENGINE_DEFAULTKEYBOARDSTATEBUILDER_H
#define DENGINE_DEFAULTKEYBOARDSTATEBUILDER_H

#include "KeyboardStateBuilder.h"

namespace dengine {
    class Key;
}

namespace dengine {
    class DefaultKeyboardStateBuilder : public KeyboardStateBuilder {
    private:
        std::set<std::unique_ptr<Key>> pressedKeys;
        std::set<std::unique_ptr<Key>> releasedKeys;
        std::string layoutCode, layoutName;
    public:
        void addPressedKey(std::unique_ptr<Key> key);

        void addReleasedKey(std::unique_ptr<Key> key);

        void setCurrentKeyboardLayoutCode(std::string layoutCode);

        void setCurrentKeyboardLayoutName(std::string layoutName);

        std::unique_ptr<KeyboardState> build();
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATEBUILDER_H
