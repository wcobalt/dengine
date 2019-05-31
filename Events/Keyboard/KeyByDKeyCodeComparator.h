//
// Created by wcobalt on 5/31/19.
//

#ifndef DENGINE_KEYBYDKEYCODECOMPARATOR_H
#define DENGINE_KEYBYDKEYCODECOMPARATOR_H

#include "KeyCode.h"

namespace dengine::events::keyboard {
    class KeyByDKeyCodeComparator {
    public:
        bool operator()(DKeyCode a, DKeyCode b) const;
    };
}

#endif //DENGINE_KEYBYDKEYCODECOMPARATOR_H
