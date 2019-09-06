//
// Created by wcobalt on 24.08.19.
//
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <fstream>
#include <iostream>

#include "XDefaultKeyboardConverter.h"
#include "../../../../Events/Keyboard/Keyboard.h"
#include "../../../../Exceptions/IOException.h"

using namespace dengine::platform::window::x::util;
using namespace dengine::events::keyboard;
using namespace dengine::exceptions;

void XDefaultKeyboardConverter::initialize(Display *display) {
    this->display = display;

    loadXKeyCodeToDKeyCodeMap();
    loadXKeySymToUtf8SymbolMap();
}

DKeyCode XDefaultKeyboardConverter::convertXKeyCodeToDKeyCode(XEvent *xEvent) {
    auto it = xKeyCodeToDKeyCodeMap.find(xEvent->xkey.keycode);

    if (it != xKeyCodeToDKeyCodeMap.end())
        return it->second;
    else
        return Keyboard::NONE;
}

std::string XDefaultKeyboardConverter::convertXKeyCodeToSymbol(XEvent *xEvent) {
    KeySym xKeySym = XkbKeycodeToKeysym(display, xEvent->xkey.keycode, group, xEvent->xkey.state & ShiftMask ? 1 : 0);

    auto it = xKeySymToUtf8SymbolMap.find(xKeySym);

    if (it != xKeySymToUtf8SymbolMap.end())
        return it->second;
    else
        return "";
}

void XDefaultKeyboardConverter::loadXKeyCodeToDKeyCodeMap() {
    for (int i = 0; i < 26; i++) //alphabet -26 chars
        addKeyCodeBinding(XK_A + i, Keyboard::A + i);

    for (int i = 0; i < 10; i++) { //digit pad, numpad -20 chars
        addKeyCodeBinding(XK_0 + i, Keyboard::A_0 + i);
        addKeyCodeBinding(XK_KP_0 + i, Keyboard::NUM_0 + i);
    }

    for (int i = 0; i < 12; i++) //functions -12 chars
        addKeyCodeBinding(XK_F1 + i, Keyboard::F1 + i);
    
    //overall 132 - 58 = 74

    addKeyCodeBinding(XK_Tab, Keyboard::TAB); //some shit, may be if i'd aligned my keys as corresponding keys are aligned in keysymdef.h...
    addKeyCodeBinding(XK_Escape, Keyboard::ESC);
    addKeyCodeBinding(XK_Caps_Lock, Keyboard::CAPS_LOCK);
    addKeyCodeBinding(XK_Shift_L, Keyboard::LEFT_SHIFT);
    addKeyCodeBinding(XK_Shift_R, Keyboard::RIGHT_SHIFT);
    addKeyCodeBinding(XK_Control_L, Keyboard::LEFT_CONTROL);
    addKeyCodeBinding(XK_Control_R, Keyboard::RIGHT_CONTROL);
    addKeyCodeBinding(XK_Alt_L, Keyboard::LEFT_ALT);
    addKeyCodeBinding(XK_Alt_R, Keyboard::RIGHT_ALT);
    addKeyCodeBinding(XK_Return, Keyboard::ENTER);
    addKeyCodeBinding(XK_BackSpace, Keyboard::BACKSPACE);
    addKeyCodeBinding(XK_Delete, Keyboard::DELETE);
    addKeyCodeBinding(XK_Super_L, Keyboard::LEFT_WIN);
    addKeyCodeBinding(XK_Super_R, Keyboard::RIGHT_WIN);
    addKeyCodeBinding(XK_Menu, Keyboard::MENU);
    addKeyCodeBinding(XK_Insert, Keyboard::INSERT);
    addKeyCodeBinding(XK_Print, Keyboard::PRINT_SCREEN);
    addKeyCodeBinding(XK_Home, Keyboard::HOME);
    addKeyCodeBinding(XK_End, Keyboard::END);
    addKeyCodeBinding(XK_Page_Up, Keyboard::PAGE_UP);
    addKeyCodeBinding(XK_Page_Down, Keyboard::PAGE_DOWN);
    addKeyCodeBinding(XK_Num_Lock, Keyboard::NUM_LOCK);
    addKeyCodeBinding(XK_Pause, Keyboard::PAUSE);
    addKeyCodeBinding(XK_Break, Keyboard::BREAK);
    addKeyCodeBinding(XK_Sys_Req, Keyboard::SYS_REQ);
    addKeyCodeBinding(XK_Scroll_Lock, Keyboard::SCROLL_LOCK);
    addKeyCodeBinding(XK_Up, Keyboard::UP);
    addKeyCodeBinding(XK_Down, Keyboard::DOWN);
    addKeyCodeBinding(XK_Left, Keyboard::LEFT);
    addKeyCodeBinding(XK_Right, Keyboard::RIGHT);
    addKeyCodeBinding(XK_KP_Divide, Keyboard::NUM_DIVIDE);
    addKeyCodeBinding(XK_KP_Multiply, Keyboard::NUM_MULTIPLY);
    addKeyCodeBinding(XK_KP_Subtract, Keyboard::NUM_SUBTRACT);
    addKeyCodeBinding(XK_KP_Add, Keyboard::NUM_ADD);
    addKeyCodeBinding(XK_KP_Enter, Keyboard::NUM_ENTER);
    addKeyCodeBinding(XK_KP_Insert, Keyboard::NUM_INSERT);
    addKeyCodeBinding(XK_KP_Delete, Keyboard::NUM_DELETE);
    addKeyCodeBinding(XK_KP_Home, Keyboard::NUM_HOME);
    addKeyCodeBinding(XK_KP_End, Keyboard::NUM_END);
    addKeyCodeBinding(XK_KP_Page_Up, Keyboard::NUM_PAGE_UP);
    addKeyCodeBinding(XK_KP_Page_Down, Keyboard::NUM_PAGE_DOWN);
    addKeyCodeBinding(XK_space, Keyboard::SPACE);
    addKeyCodeBinding(XK_minus, Keyboard::MINUS);
    addKeyCodeBinding(XK_underscore, Keyboard::UNDERSCORE);
    addKeyCodeBinding(XK_plus, Keyboard::PLUS);
    addKeyCodeBinding(XK_equal, Keyboard::EQUALS);
    addKeyCodeBinding(XK_braceleft, Keyboard::LEFT_BRACE);
    addKeyCodeBinding(XK_braceright, Keyboard::RIGHT_BRACE);
    addKeyCodeBinding(XK_bracketleft, Keyboard::LEFT_SQUARE);
    addKeyCodeBinding(XK_bracketright, Keyboard::RIGHT_SQUARE);
    addKeyCodeBinding(XK_colon, Keyboard::COLON);
    addKeyCodeBinding(XK_semicolon, Keyboard::SEMICOLON);
    addKeyCodeBinding(XK_apostrophe, Keyboard::APOSTROPHE);
    addKeyCodeBinding(XK_quotedbl, Keyboard::DOUBLE_QUOTE);
    addKeyCodeBinding(XK_bar, Keyboard::PIPE);
    addKeyCodeBinding(XK_slash, Keyboard::SLASH);
    addKeyCodeBinding(XK_backslash, Keyboard::BACKSLASH);
    addKeyCodeBinding(XK_less, Keyboard::LESS);
    addKeyCodeBinding(XK_greater, Keyboard::GREATER);
    addKeyCodeBinding(XK_comma, Keyboard::COMMA);
    addKeyCodeBinding(XK_period, Keyboard::PERIOD);
    addKeyCodeBinding(XK_question, Keyboard::QUESTION);
    addKeyCodeBinding(XK_exclam, Keyboard::EXCLAMATION);
    addKeyCodeBinding(XK_asciitilde, Keyboard::TILDE);
    addKeyCodeBinding(XK_grave, Keyboard::GRAVE);
    addKeyCodeBinding(XK_at, Keyboard::AT);
    addKeyCodeBinding(XK_numbersign, Keyboard::SHARP);
    addKeyCodeBinding(XK_dollar, Keyboard::DOLLAR);
    addKeyCodeBinding(XK_percent, Keyboard::PERCENTS);
    addKeyCodeBinding(XK_asciicircum, Keyboard::CIRCUMFLEX);
    addKeyCodeBinding(XK_ampersand, Keyboard::AMPERSAND);
    addKeyCodeBinding(XK_asterisk, Keyboard::ASTERISK);
    addKeyCodeBinding(XK_parenleft, Keyboard::LEFT_PARENTHESIS);
    addKeyCodeBinding(XK_parenright, Keyboard::RIGHT_PARENTHESIS);
}

void XDefaultKeyboardConverter::addKeyCodeBinding(int keyCode, DKeyCode dKeyCode) {
    xKeyCodeToDKeyCodeMap.insert(std::make_pair(XKeysymToKeycode(this->display, keyCode), dKeyCode));
}

void XDefaultKeyboardConverter::loadXKeySymToUtf8SymbolMap() {
    std::ifstream input(XKEYSYMS_TABLE_FILE, std::fstream::binary);

    int length = 0;
    int expectedLength = 0;
    int state = 0;
    KeySym keysym = 0;
    std::string utf8symbol;

    if (!input.good()) throw IOException("Cannot open " + XKEYSYMS_TABLE_FILE + " file");

    int index = 0;

    while (input.good()) {
        index++;
        unsigned char ch = 0;

        input.read((char*)&ch, 1);

        switch (state) {
            case 0:
                keysym |= ch;
                length++;

                if (length == 4) {
                    length = 0;
                    state = 1;
                } else
                    keysym <<= 8;

                break;
            case 1:
                if (length == 0) {
                    expectedLength = 0;

                    for (int i = 0; i < BYTE_SIZE; i++) {
                        if (((ch >> (BYTE_SIZE - i - 1)) & 1) == 0) {
                            if (i == 0) expectedLength = 1;
                            else
                                expectedLength = i;

                            break;
                        }
                    }

                    length = 0;
                }

                if (length < expectedLength) {
                    utf8symbol += ch;
                    length++;

                    if (length == expectedLength) {
                        length = 0;
                        state = 0;

                        xKeySymToUtf8SymbolMap.insert(std::make_pair(keysym, utf8symbol));

                        keysym = 0;
                        utf8symbol.clear();
                    }
                }

                break;
        }
    }
}

void XDefaultKeyboardConverter::setGroup(int group) {
    this->group = group;
}