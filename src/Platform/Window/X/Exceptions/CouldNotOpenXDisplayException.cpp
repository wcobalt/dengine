//
// Created by wcobalt on 5/31/19.
//

#include "CouldNotOpenXDisplayException.h"

using namespace dengine::platform::window::x::exceptions;

const char* CouldNotOpenXDisplayException::what() const noexcept {
    return "Could not open XDisplay. Make sure if XServer is installed.";
}