//
// Created by wcobalt on 22.08.19.
//
#include <string>

#ifndef DENGINE_XKEYBOARDDRIVER_H
#define DENGINE_XKEYBOARDDRIVER_H

#include "../../../../Events/Keyboard/KeyCode.h";

namespace dengine::platform::window::x::drivers {
    class XKeyboardDriver {
    public:
        virtual void initialize() = 0;

        virtual dengine::events::keyboard::DKeyCode convertXKeyCodeToDKeyCode(int xKeyCode) = 0;

        virtual std::string convertXKeyCodeToSymbol(int xKeyCode) = 0;
    };
}


#endif //DENGINE_XKEYBOARDDRIVER_H
