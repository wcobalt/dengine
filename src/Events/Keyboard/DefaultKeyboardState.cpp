//
// Created by wcobalt on 23.05.19.
//

#include <set>
#include <memory>

#include "DefaultKeyboardState.h"
#include "Keyboard.h"
#include "KeyByDKeyCodeComparator.h"
#include "KeyBySymbolComparator.h"
#include "DKey.h"

using namespace dengine;

DefaultKeyboardState::DefaultKeyboardState(const std::set<std::shared_ptr<Key>>& pressedKeys,
                                           const std::set<std::shared_ptr<Key>>& releasedKeys,
                                           const std::string& keyboardLayoutCode, const std::string& keyboardLayoutName):
                                            keyboardLayoutCode(keyboardLayoutCode), keyboardLayoutName(keyboardLayoutName) {

    pressedKeysIndexDKeyCode.insert(pressedKeys.begin(), pressedKeys.end());
    pressedKeysIndexSymbol.insert(pressedKeys.begin(), pressedKeys.end());
    this->pressedKeys.insert(pressedKeys.begin(), pressedKeys.end());

    releasedKeysIndexDKeyCode.insert(releasedKeys.begin(), releasedKeys.end());
    releasedKeysIndexSymbol.insert(releasedKeys.begin(), releasedKeys.end());
    this->releasedKeys.insert(releasedKeys.begin(), releasedKeys.end());
}

bool DefaultKeyboardState::isKeyPressed(DKeyCode key) const {
    return pressedKeysIndexDKeyCode.find(std::make_shared<DKey>(key, "")) != pressedKeysIndexDKeyCode.end();
}

bool DefaultKeyboardState::isKeyReleased(DKeyCode key) const {
    return releasedKeysIndexDKeyCode.find(std::make_shared<DKey>(key, "")) != releasedKeysIndexDKeyCode.end();
}

bool DefaultKeyboardState::isSymbolPressed(const std::string &symbol) const {
    return pressedKeysIndexSymbol.find(std::make_shared<DKey>(0, symbol)) != pressedKeysIndexSymbol.end();
}

bool DefaultKeyboardState::isSymbolReleased(const std::string &symbol) const {
    return releasedKeysIndexSymbol.find(std::make_shared<DKey>(0, symbol)) != releasedKeysIndexSymbol.end();
}

std::string DefaultKeyboardState::getCurrentKeyboardLayoutCode() const {
    return keyboardLayoutCode;
}

std::string DefaultKeyboardState::getCurrentKeyboardLayoutName() const {
    return keyboardLayoutName;
}

std::set<std::shared_ptr<Key>> DefaultKeyboardState::getAllPressedKeys() const {
    return pressedKeys;
}

std::set<std::shared_ptr<Key>> DefaultKeyboardState::getAllReleasedKeys() const {
    return releasedKeys;
}
