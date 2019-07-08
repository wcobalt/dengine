//
// Created by wcobalt on 5/30/19.
//

#include <string>

#include "DKey.h"
#include "KeyCode.h"

using std::string;

using namespace dengine::events::keyboard;

DKey::DKey(DKeyCode keycode, const string &symbol) {
    this->keycode = keycode;
    this->symbol = symbol;
}

DKeyCode DKey::getKeycode() const {
    return keycode;
}

string DKey::getSymbol() const {
    return symbol;
}