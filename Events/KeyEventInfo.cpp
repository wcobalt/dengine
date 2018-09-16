//
// Created by wcobalt on 16.09.18.
//

#include "KeyEventInfo.h"

KeyEventInfo::KeyEventInfo(unsigned int keyCode) {
    this->keyCode = keyCode;
}

unsigned int KeyEventInfo::getKeyCode() {
    return keyCode;
}