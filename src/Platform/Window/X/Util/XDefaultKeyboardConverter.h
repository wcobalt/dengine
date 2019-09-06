//
// Created by wcobalt on 24.08.19.
//

#include <string>
#include <map>
#include <X11/Xlib.h>

#ifndef DENGINE_XDEFAULTKEYBOARDCONVERTER_H
#define DENGINE_XDEFAULTKEYBOARDCONVERTER_H

#include "../../../../Events/Keyboard/Keyboard.h"
#include "XKeyboardConverter.h"

namespace dengine::platform::window::x::util {
    class XDefaultKeyboardConverter : public XKeyboardConverter {
    private:
        std::map<KeyCode, events::keyboard::DKeyCode> xKeyCodeToDKeyCodeMap;
        std::map<KeySym, std::string> xKeySymToUtf8SymbolMap;

        Display* display;
        int group = 0;

        void loadXKeyCodeToDKeyCodeMap();
        void loadXKeySymToUtf8SymbolMap();
        void addKeyCodeBinding(int keyCode, dengine::events::keyboard::DKeyCode dKeyCode);

        const unsigned BYTE_SIZE = 8;
    public:
        const std::string XKEYSYMS_TABLE_FILE = "xkeysyms";

        void initialize(Display *display);

        events::keyboard::DKeyCode convertXKeyCodeToDKeyCode(XEvent *xEvent);

        std::string convertXKeyCodeToSymbol(XEvent *xEvent);

        void setGroup(int group) override;
    };
}

#endif //DENGINE_XDEFAULTKEYBOARDCONVERTER_H
