//
// Created by wcobalt on 16.09.18.
//

#include "MouseEventInfo.h"

MouseEventInfo::MouseEventInfo(int x, int y) {
    this->x = x;
    this->y = y;
}

int MouseEventInfo::getX() {
    return x;
}

int MouseEventInfo::getY() {
    return y;
}
