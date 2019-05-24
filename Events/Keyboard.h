//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_KEYBOARD_H
#define DENGINE_KEYBOARD_H

namespace dengine::events {
    static const int
            TAB_KEY = 0,
            ESC_KEY = 1,
            CAPSLOCK_KEY = 2,
            LEFT_SHIFT_KEY = 3,
            RIGHT_SHIFT_KEY = 4,
            LEFT_CONTROL_KEY = 5,
            RIGHT_CONTROL_KEY = 6,
            SPACE_KEY = 7,
            LEFT_ALT_KEY = 8,
            RIGHT_ALT_KEY = 9,
            ENTER_KEY = 10, //@TODO CRITICAL: NUMPAD CRITICAL
            BACKSPACE_KEY = 0,
            F1_KEY = 0,
            F2_KEY = 0,
            F3_KEY = 0,
            F4_KEY = 0,
            F5_KEY = 0,
            F6_KEY = 0,
            F7_KEY = 0,
            F8_KEY = 0,
            F9_KEY = 0,
            F10_KEY = 0,
            F11_KEY = 0,
            F12_KEY = 0,
            DELETE_KEY = 0, //@TODO CRITICAL: NUMPAD CRITICAL
            WIN_KEY = 0,
            CONTEXT_MENU_KEY = 0,
            INSERT_KEY = 0,
            PRINT_SCREEN_KEY = 0,
            HOME_KEY = 0,
            END_KEY = 0,
            PAGE_UP_KEY = 0,
            PAGE_DOWN_KEY = 0,
            NUMPAD_LOCK_KEY = 0,
            PAUSE_KEY = 0,
            BREAK_KEY = 0,
            SYSTEM_REQUEST_KEY = 0,
            SCROLL_LOCK_KEY = 0,
            TOP_ARROW_KEY = 0,
            DOWN_ARROW_KEY = 0,
            LEFT_ARROW_KEY = 0,
            RIGHT_ARROW_KEY = 0;

    class Keyboard {
    public:
        static int ord(char ch);
    };
}

#endif //DENGINE_KEYBOARD_H
