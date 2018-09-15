//
// Created by wcobalt on 15.09.18.
//

#include "MouseEventParameters.h"

MouseEventParameters::MouseEventParameters(int x, int y) {
    //@TODO initilize superclass
    this->x = x;
    this->y = y;
}

int MouseEventParameters::getX() {
    return x;
}

int MouseEventParameters::getY() {
    return y;
}