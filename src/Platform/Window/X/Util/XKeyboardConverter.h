//
// Created by wcobalt on 22.08.19.
//
#include <string>

#ifndef DENGINE_XKEYBOARDDRIVER_H
#define DENGINE_XKEYBOARDDRIVER_H

#include "../../../../Events/Keyboard/Keyboard.h"

namespace dengine::platform::window::x::util {
    class XKeyboardConverter {
    public:
        virtual void initialize(Display *display) = 0;

        virtual events::keyboard::DKeyCode convertXKeyCodeToDKeyCode(XEvent *xEvent) = 0;

        virtual std::string convertXKeyCodeToSymbol(XEvent *xEvent) = 0;

        virtual void setGroup(int group) = 0;
    };
}


#endif //DENGINE_XKEYBOARDDRIVER_H
