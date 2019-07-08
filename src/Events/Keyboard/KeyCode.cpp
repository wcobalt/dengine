//
// Created by wcobalt on 23.05.19.
//

#include "KeyCode.h"

using namespace dengine::events::keyboard;

int KeyCode::ord(char ch) {
    return BASE + ch;//non-safe, for non defined in key symbols
}