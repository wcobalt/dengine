//
// Created by wcobalt on 16.09.18.
//

#include "MouseButtonEventInfo.h"

MouseButtonEventInfo::MouseButtonEventInfo(int x, int y, unsigned int buttonCode)
    :MouseEventInfo(x, y) {

    this->buttonCode = buttonCode;
}

unsigned int MouseButtonEventInfo::getButtonCode() {
    return buttonCode;
}