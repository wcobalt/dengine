//
// Created by wcobalt on 24.08.19.
//

#include "XDefaultKeyboardConverter.h"
#include "../../../../Events/Keyboard/KeyCode.h"

using namespace dengine::platform::window::x::util;
using namespace dengine::events::keyboard;

void XDefaultKeyboardConverter::initialize() {

}

DKeyCode XDefaultKeyboardConverter::convertXKeyCodeToDKeyCode(int xKeyCode) {
    return 0;
}

std::string XDefaultKeyboardConverter::convertXKeyCodeToSymbol(int xKeyCode) {
    return std::__cxx11::string();
}
