//
// Created by wcobalt on 23.05.19.
//

#include <set>

#include "DefaultKeyboardState.h"
#include "KeyCode.h"
#include "KeyByDKeyCodeComparator.h"
#include "KeyBySymbolComparator.h"
#include "DKey.h"

using namespace dengine::events::keyboard;

DefaultKeyboardState::DefaultKeyboardState(const std::set<Key>& pressedKeys, const std::set<Key>& releasedKeys,
                                           const std::string& keyboardLayoutCode, const std::string& keyboardLayoutName):
                                            keyboardLayoutCode(keyboardLayoutCode), keyboardLayoutName(keyboardLayoutName) {

    pressedKeysIndexDKeyCode.insert(pressedKeys.begin(), pressedKeys.end());
    pressedKeysIndexSymbol.insert(pressedKeys.begin(), pressedKeys.end());

    releasedKeysIndexDKeyCode.insert(releasedKeys.begin(), releasedKeys.end());
    releasedKeysIndexSymbol.insert(releasedKeys.begin(), releasedKeys.end());
}

bool DefaultKeyboardState::isKeyPressed(DKeyCode key) const {
    return pressedKeysIndexDKeyCode.find(DKey(key, "")) != pressedKeysIndexDKeyCode.end();
}

bool DefaultKeyboardState::isKeyReleased(DKeyCode key) const {
    return releasedKeysIndexDKeyCode.find(DKey(key, "")) != releasedKeysIndexDKeyCode.end();
}

bool DefaultKeyboardState::isSymbolPressed(const std::string &symbol) const {
    return pressedKeysIndexSymbol.find(DKey(0, symbol)) != pressedKeysIndexSymbol.end();
}

bool DefaultKeyboardState::isSymbolReleased(const std::string &symbol) const {
    return releasedKeysIndexSymbol.find(DKey(0, symbol)) != releasedKeysIndexSymbol.end();
}

std::string DefaultKeyboardState::getCurrentKeyboardLayoutCode() const {
    return keyboardLayoutCode;
}

std::string DefaultKeyboardState::getCurrentKeyboardLayoutName() const {
    return keyboardLayoutName;
}