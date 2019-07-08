//
// Created by wcobalt on 5/29/19.
//

#ifndef DENGINE_KEYCODE_H
#define DENGINE_KEYCODE_H

namespace dengine::events::keyboard {
    typedef int DKeyCode;
    
    class KeyCode {
    private:
        static const int BASE = 255;
    public:
        //NONSYMBOLS ARE THERE
        static const DKeyCode TAB = 0,
        ESC = 1,
        CAPSLOCK = 2,
        LEFT_SHIFT = 3,
        RIGHT_SHIFT = 4,
        LEFT_CONTROL = 5,
        RIGHT_CONTROL = 6,
        LEFT_ALT = 7,
        RIGHT_ALT = 8,
        ENTER = 9,
        BACKSPACE = 10,
        F1 = 11,
        F2 = 12,
        F3 = 13,
        F4 = 14,
        F5 = 15,
        F6 = 16,
        F7 = 17,
        F8 = 18,
        F9 = 19,
        F10 = 20,
        F11 = 21,
        F12 = 22,
        DELETE = 23,
        LEFT_WIN = 24,
        RIGHT_WIN = 25,
        //COMMAND????
        MENU = 26,
        INSERT = 27,
        PRINT_SCREEN = 28,
        HOME = 29,
        END = 30,
        PAGE_UP = 31,
        PAGE_DOWN = 32,
        NUM_LOCK = 33,
        PAUSE = 34,
        BREAK = 35,
        SYS_REQ = 36,
        SCROLL_LOCK = 37,
        TOP_ARROW = 38,
        DOWN_ARROW = 39,
        LEFT_ARROW = 40,
        RIGHT_ARROW = 41,
        NUM_DIVIDE = 42,
        NUM_MULTIPLY = 43,
        NUM_MINUS = 44,
        NUM_PLUS = 45,
        NUM_ENTER = 46,
        NUM_PERIOD = 47,
        NUM_0 = 48,
        NUM_1 = 49,
        NUM_2 = 50,
        NUM_3 = 51,
        NUM_4 = 52,
        NUM_5 = 53,
        NUM_6 = 54,
        NUM_7 = 55,
        NUM_8 = 56,
        NUM_9 = 57,
        //SYMBOLS ARE THERE
        SPACE = BASE + ' ',
        Q = BASE + 'Q', W = BASE + 'W', E = BASE + 'E', R = BASE + 'R', T = BASE + 'T', Y = BASE + 'Y', U = BASE + 'U',
        I = BASE + 'I', O = BASE + 'O', P = BASE + 'P', A = BASE + 'A', S = BASE + 'S', D = BASE + 'D', F = BASE + 'F',
        G = BASE + 'G', H = BASE + 'H', J = BASE + 'J', K = BASE + 'K', L = BASE + 'L', Z = BASE + 'Z', X = BASE + 'X',
        C = BASE + 'C', V = BASE + 'V', B = BASE + 'B', N = BASE + 'N', M = BASE + 'M',
        A0 = BASE + '0', A1 = BASE + '1', A2 = BASE + '2', A3 = BASE + '3', A4 = BASE + '4',
        A5 = BASE + '5', A6 = BASE + '6', A7 = BASE + '7', A8 = BASE + '8', A9 = BASE + '9',
        MINUS = BASE + '-',
        UNDERSCORE = BASE + '_',
        PLUS = BASE + '+',
        EQUALS = BASE + '=',
        LEFT_CURLY = BASE + '{',
        RIGHT_CURLY = BASE + '}',
        LEFT_SQUARE = BASE + '[',
        RIGHT_SQUARE = BASE + ']',
        COLON = BASE + ':',
        SEMICOLON = BASE + ';',
        QUOTE = BASE + '\'',
        DOUBLE_QUOTE = BASE + '"',
        PIPE = BASE + '|',
        SLASH = BASE + '/',
        BACKSLASH = BASE + '\\',
        LEFT_ANGLE = BASE + '<',
        RIGHT_ANGLE = BASE + '>',
        COMMA = BASE + ',',
        PERIOD = BASE + '.',
        QUESTION = BASE + '?',
        EXCLAMATION = BASE + '!',
        TILDE = BASE + '~',
        BACK_QUOTE = BASE + '`',
        AT = BASE + '@',
        SHARP = BASE + '#',
        DOLLAR = BASE + '$',
        PERCENTS = BASE + '%',
        CIRCUMFLEX = BASE + '^',
        AMPERSAND = BASE + '&',
        ASTERISK = BASE + '*',
        LEFT_PAREN = BASE + '(',
        RIGHT_PAREN = BASE + ')';

        static int ord(char ch);
    };
}

#endif //DENGINE_KEYCODE_H
