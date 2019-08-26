//
// Created by wcobalt on 24.08.19.
//

#include <string>

#ifndef DENGINE_XDEFAULTKEYBOARDCONVERTER_H
#define DENGINE_XDEFAULTKEYBOARDCONVERTER_H

#include "XKeyboardConverter.h"

namespace dengine::platform::window::x::util {
    class XDefaultKeyboardConverter : public XKeyboardConverter {
    public:
        void initialize();

        events::keyboard::DKeyCode convertXKeyCodeToDKeyCode(int xKeyCode);

        std::string convertXKeyCodeToSymbol(int xKeyCode);
    };
}

#endif //DENGINE_XDEFAULTKEYBOARDCONVERTER_H
