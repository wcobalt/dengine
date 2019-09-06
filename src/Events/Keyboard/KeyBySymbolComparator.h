//
// Created by wcobalt on 5/31/19.
//
#include <memory>

#ifndef DENGINE_KEYBYSYMBOLCOMPARATOR_H
#define DENGINE_KEYBYSYMBOLCOMPARATOR_H

#include "KeyComparator.h"

namespace dengine {
    class Key;
}

namespace dengine {
    class KeyBySymbolComparator : public KeyComparator {
    public:
        bool operator()(const std::shared_ptr<Key>& a, const std::shared_ptr<Key>& b) const;
    };
}

#endif //DENGINE_KEYBYSYMBOLCOMPARATOR_H
