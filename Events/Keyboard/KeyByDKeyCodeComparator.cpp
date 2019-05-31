//
// Created by wcobalt on 5/31/19.
//

#include "KeyByDKeyCodeComparator.h"
#include "KeyCode.h"

using namespace dengine::events::keyboard;

bool KeyByDKeyCodeComparator::operator()(DKeyCode a, DKeyCode b) const {
    return a > b;
}