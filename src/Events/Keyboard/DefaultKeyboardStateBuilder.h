//
// Created by wcobalt on 22.08.19.
//
#include <string>
#include <set>
#include <memory>

#ifndef DENGINE_DEFAULTKEYBOARDSTATEBUILDER_H
#define DENGINE_DEFAULTKEYBOARDSTATEBUILDER_H

#include "KeyboardStateBuilder.h"

namespace dengine::events::keyboard {
    class Key;
}

namespace dengine::events::keyboard {
    class DefaultKeyboardStateBuilder : public KeyboardStateBuilder {
    private:
        std::set<std::shared_ptr<Key>> pressedKeys;
        std::set<std::shared_ptr<Key>> releasedKeys;
        std::string layoutCode, layoutName;
    public:
        DefaultKeyboardStateBuilder();

        void addPressedKey(std::shared_ptr<Key> key);

        void addReleasedKey(std::shared_ptr<Key> key);

        void setCurrentKeyboardLayoutCode(const std::string &layoutCode);

        void setCurrentKeyboardLayoutName(const std::string &layoutName);

        std::shared_ptr<KeyboardState> build();
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATEBUILDER_H
