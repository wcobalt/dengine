//
// Created by wcobalt on 22.08.19.
//

#include "DefaultKeyboardStateBuilder.h"
#include "Key.h"
#include "DefaultKeyboardState.h"
#include "KeyboardState.h"

using namespace dengine;

void DefaultKeyboardStateBuilder::addPressedKey(std::unique_ptr<Key> key) {
    pressedKeys.insert(std::move(key));
}

void DefaultKeyboardStateBuilder::addReleasedKey(std::unique_ptr<Key> key) {
    releasedKeys.insert(std::move(key));
}

void DefaultKeyboardStateBuilder::setCurrentKeyboardLayoutCode(std::string layoutCode) {
    this->layoutCode = std::move(layoutCode);
}

void DefaultKeyboardStateBuilder::setCurrentKeyboardLayoutName(std::string layoutName) {
    this->layoutName = std::move(layoutName);
}

std::unique_ptr<KeyboardState> DefaultKeyboardStateBuilder::build() {
    return std::make_unique<DefaultKeyboardState>(std::move(pressedKeys),
            std::move(releasedKeys),
            layoutCode, layoutName);
}