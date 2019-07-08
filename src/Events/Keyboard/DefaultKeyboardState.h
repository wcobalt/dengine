//
// Created by wcobalt on 23.05.19.
//

#include <set>

#ifndef DENGINE_DEFAULTKEYBOARDSTATE_H
#define DENGINE_DEFAULTKEYBOARDSTATE_H

#include "KeyboardState.h"
#include "KeyCode.h"
#include "KeyByDKeyCodeComparator.h"
#include "KeyBySymbolComparator.h"

namespace dengine::events::keyboard {
    class Key;
}

namespace dengine::events::keyboard {
    class DefaultKeyboardState : public KeyboardState {
    private:
        std::set<std::shared_ptr<Key>, KeyByDKeyCodeComparator> pressedKeysIndexDKeyCode;
        std::set<std::shared_ptr<Key>, KeyByDKeyCodeComparator> releasedKeysIndexDKeyCode;

        std::set<std::shared_ptr<Key>, KeyBySymbolComparator> pressedKeysIndexSymbol;
        std::set<std::shared_ptr<Key>, KeyBySymbolComparator> releasedKeysIndexSymbol;

        std::string keyboardLayoutCode, keyboardLayoutName;
    public:
        DefaultKeyboardState(const std::set<std::shared_ptr<Key>>& pressedKeys,
                             const std::set<std::shared_ptr<Key>>& releasedKeys,
                             const std::string& keyboardLayoutCode, const std::string& keyboardLayoutName);

        bool isKeyPressed(DKeyCode key) const;

        bool isKeyReleased(DKeyCode key) const;

        bool isSymbolPressed(const std::string& symbol) const;

        bool isSymbolReleased(const std::string& symbol) const;

        std::string getCurrentKeyboardLayoutCode() const; //@todo implement after release

        std::string getCurrentKeyboardLayoutName() const; //@todo implement after release
    };
}

#endif //DENGINE_DEFAULTKEYBOARDSTATE_H
