//
// Created by wcobalt on 6/10/19.
//

#include "TraySpecificationIsNotSupportedException.h"

using namespace dengine::platform::window::x::exceptions;

const char* TraySpecificationIsNotSupportedException::what() const noexcept {
    return "Tray specification is not supported by this desktop environment/window manager. I'm sorry";
}