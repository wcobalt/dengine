//
// Created by wcobalt on 23.05.19.
//

#include "Keyboard.h"

using namespace dengine;

int Keyboard::ord(char ch) {
    return BASE + ch;//non-safe, for non defined in key symbols
}