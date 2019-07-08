//
// Created by wcobalt on 5/30/19.
//

#include <string>

#ifndef DENGINE_KEY_H
#define DENGINE_KEY_H

#include "KeyCode.h"
#include "../../DObject.h"

namespace dengine::events::keyboard {
    class Key : public DObject {
    public:
        virtual DKeyCode getKeycode() const = 0;

        virtual std::string getSymbol() const = 0;
    };
}

#endif //DENGINE_KEY_H
