//
// Created by wcobalt on 22.08.19.
//

#include "DefaultKeyboardStateBuilder.h"
#include "Key.h"
#include "DefaultKeyboardState.h"

using namespace dengine::events::keyboard;

DefaultKeyboardStateBuilder::DefaultKeyboardStateBuilder() {

}


void DefaultKeyboardStateBuilder::addPressedKey(std::shared_ptr<Key> key) {
    pressedKeys.insert(key);
}

void DefaultKeyboardStateBuilder::addReleasedKey(std::shared_ptr<Key> key) {
    releasedKeys.insert(key);
}

void DefaultKeyboardStateBuilder::setCurrentKeyboardLayoutCode(const std::string &layoutCode) {
    this->layoutCode = layoutCode;
}

void DefaultKeyboardStateBuilder::setCurrentKeyboardLayoutName(const std::string &layoutName) {
    this->layoutName = layoutName;
}

std::shared_ptr<KeyboardState> DefaultKeyboardStateBuilder::build() {
    return std::make_shared<DefaultKeyboardState>(pressedKeys, releasedKeys, layoutCode, layoutName);
}