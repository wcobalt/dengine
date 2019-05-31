//
// Created by wcobalt on 5/31/19.
//

#include <string>

#ifndef DENGINE_KEYBYSYMBOLCOMPARATOR_H
#define DENGINE_KEYBYSYMBOLCOMPARATOR_H

namespace dengine::events::keyboard {
    class KeyBySymbolComparator {
    public:
        bool operator()(const std::string& a, const std::string& b) const;
    };
}

#endif //DENGINE_KEYBYSYMBOLCOMPARATOR_H
