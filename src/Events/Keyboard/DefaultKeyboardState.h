//
// Created by wcobalt on 23.05.19.
//

#include <set>
#include <unordered_map>
#include <string_view>

#ifndef DENGINE_DEFAULTKEYBOARDSTATE_H
#define DENGINE_DEFAULTKEYBOARDSTATE_H

#include "KeyboardState.h"
#include "Keyboard.h"

namespace dengine {
    class Key;
}

namespace dengine {
    class DefaultKeyboardState : public KeyboardState {
    private:
        std::set<std::unique_ptr<Key>> pressedKeys;
        std::set<std::unique_ptr<Key>> releasedKeys;

        std::set<Key*> pressedKeysFrontend;
        std::set<Key*> releasedKeysFrontend;

        std::set<DKeyCode> pressedKeysIndexDKeyCode;
        std::set<DKeyCode> releasedKeysIndexDKeyCode;

        std::set<std::string_view> pressedKeysIndexSymbol;
        std::set<std::string_view> releasedKeysIndexSymbol;

        std::string keyboardLayoutCode, keyboardLayoutName;
    public:
        DefaultKeyboardState(std::set<std::unique_ptr<Key>> pressedKeys,
                             std::set<std::unique_ptr<Key>> releasedKeys,
                             std::string keyboardLayoutCode, std::string keyboardLayoutName);

        bool isKeyPressed(DKeyCode key) const;

        bool isKeyReleased(DKeyCode key) const;

        bool isSymbolPressed(std::string_view symbol) const;

        bool isSymbolReleased(std::string_view symbol) const;

        const std::string & getCurrentKeyboardLayoutCode() const; //@todo implement after release

        const std::string & getCurrentKeyboardLayoutName() const; //@todo implement after release

        const std::set<Key*> & getAllPressedKeys() const;

        const std::set<Key*> & getAllReleasedKeys() const;
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATE_H
