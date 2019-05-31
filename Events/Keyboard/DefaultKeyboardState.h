//
// Created by wcobalt on 23.05.19.
//

#include <set>

#ifndef DENGINE_DEFAULTKEYBOARDSTATE_H
#define DENGINE_DEFAULTKEYBOARDSTATE_H

#include "KeyboardState.h"
#include "Key.h"
#include "KeyCode.h"
#include "KeyByDKeyCodeComparator.h"
#include "KeyBySymbolComparator.h"

namespace dengine::events::keyboard {
    class DefaultKeyboardState : public KeyboardState {
    private:
        std::set<Key, KeyByDKeyCodeComparator> pressedKeysIndexDKeyCode;
        std::set<Key, KeyByDKeyCodeComparator> releasedKeysIndexDKeyCode;

        std::set<Key, KeyBySymbolComparator> pressedKeysIndexSymbol;
        std::set<Key, KeyBySymbolComparator> releasedKeysIndexSymbol;

        std::string keyboardLayoutCode, keyboardLayoutName;
    public:
        DefaultKeyboardState(const std::set<Key>& pressedKeys, const std::set<Key>& releasedKeys,
                             const std::string& keyboardLayoutCode, const std::string& keyboardLayoutName);

        bool isKeyPressed(DKeyCode key) const;

        bool isKeyReleased(DKeyCode key) const;

        bool isSymbolPressed(const std::string& symbol) const;

        bool isSymbolReleased(const std::string& symbol) const;

        std::string getCurrentKeyboardLayoutCode() const;

        std::string getCurrentKeyboardLayoutName() const;
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATE_H
