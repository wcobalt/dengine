//
// Created by wcobalt on 5/31/19.
//
#include <memory>

#ifndef DENGINE_KEYBYDKEYCODECOMPARATOR_H
#define DENGINE_KEYBYDKEYCODECOMPARATOR_H

#include "KeyComparator.h"

namespace dengine::events::keyboard {
    class Key;
}

namespace dengine::events::keyboard {
    class KeyByDKeyCodeComparator {
    public:
        bool operator()(const std::shared_ptr<Key>& a, const std::shared_ptr<Key>& b) const;
    };
}

#endif //DENGINE_KEYBYDKEYCODECOMPARATOR_H
