//
// Created by wcobalt on 5/30/19.
//

#include <string>

#ifndef DENGINE_DKEY_H
#define DENGINE_DKEY_H

#include "Keyboard.h"
#include "Key.h"

namespace dengine::events::keyboard {
    class DKey : public Key {
    private:
        std::string symbol;
        DKeyCode keycode;
    public:
        DKey(DKeyCode keycode, const std::string& symbol);

        DKeyCode getKeycode() const;

        std::string getSymbol() const;
    };
}

#endif //DENGINE_DKEY_H
