//
// Created by wcobalt on 5/31/19.
//

#include "NoSuitableXVisualInfoException.h"

using namespace dengine::platform::window::x::exceptions;

const char* NoSuitableXVisualInfoException::what() const noexcept {
    return "Could not get suitable XVisualInfo";
}