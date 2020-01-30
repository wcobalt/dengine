//
// Created by wcobalt on 23.05.19.
//

#include <set>
#include <memory>

#include "DefaultKeyboardState.h"
#include "Keyboard.h"
#include "DKey.h"

using namespace dengine;

DefaultKeyboardState::DefaultKeyboardState(std::set<std::unique_ptr<Key>> pressedKeys,
                                           std::set<std::unique_ptr<Key>> releasedKeys,
                                           std::string keyboardLayoutCode, std::string keyboardLayoutName):
                                            keyboardLayoutCode(std::move(keyboardLayoutCode)),
                                            keyboardLayoutName(std::move(keyboardLayoutName)),
                                            pressedKeys(std::move(pressedKeys)),
                                            releasedKeys(std::move(releasedKeys)) {

    for (auto& key : this->pressedKeys) {
        pressedKeysIndexDKeyCode.insert(key->getKeycode());
        pressedKeysIndexSymbol.insert(key->getSymbol());

        pressedKeysFrontend.insert(&*key);
    }

    for (auto& key : this->releasedKeys) {
        releasedKeysIndexDKeyCode.insert(key->getKeycode());
        releasedKeysIndexSymbol.insert(key->getSymbol());

        releasedKeysFrontend.insert(&*key);
    }
}

bool DefaultKeyboardState::isKeyPressed(DKeyCode key) const {
    return pressedKeysIndexDKeyCode.find(key) != pressedKeysIndexDKeyCode.end();
}

bool DefaultKeyboardState::isKeyReleased(DKeyCode key) const {
    return releasedKeysIndexDKeyCode.find(key) != releasedKeysIndexDKeyCode.end();
}

bool DefaultKeyboardState::isSymbolPressed(std::string_view symbol) const {
    return pressedKeysIndexSymbol.find(symbol) != pressedKeysIndexSymbol.end();
}

bool DefaultKeyboardState::isSymbolReleased(std::string_view symbol) const {
    return releasedKeysIndexSymbol.find(symbol) != releasedKeysIndexSymbol.end();
}

const std::string & DefaultKeyboardState::getCurrentKeyboardLayoutCode() const {
    return keyboardLayoutCode;
}

const std::string & DefaultKeyboardState::getCurrentKeyboardLayoutName() const {
    return keyboardLayoutName;
}

const std::set<Key*> & DefaultKeyboardState::getAllPressedKeys() const {
    return pressedKeysFrontend;
}

const std::set<Key*> & DefaultKeyboardState::getAllReleasedKeys() const {
    return releasedKeysFrontend;
}
