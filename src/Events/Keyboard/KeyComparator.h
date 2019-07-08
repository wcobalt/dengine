//
// Created by wcobalt on 7/8/19.
//
#include <memory>

#ifndef DENGINE_KEYCOMPARATOR_H
#define DENGINE_KEYCOMPARATOR_H

namespace dengine::events::keyboard {
    class Key;
}

namespace dengine::events::keyboard {
    class KeyComparator {
        bool operator()(const std::shared_ptr<Key>& a, const std::shared_ptr<Key>& b) const;
    };
}

#endif //DENGINE_KEYCOMPARATOR_H
