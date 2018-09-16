#include "MouseEventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#include "MouseScrollEventInfo.h"

MouseScrollEventInfo::MouseScrollEventInfo(int x, int y, int scrollPoints)
    :MouseEventInfo(x, y) {

    this->scrollPoints = scrollPoints;
}

int MouseScrollEventInfo::getScrollPoints() {
    return scrollPoints;
}