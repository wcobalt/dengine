//
// Created by wcobalt on 22.08.19.
//

#include "XException.h"

using namespace dengine::platform::window::x::exceptions;

XException::XException(const std::string &description):description(description) {}

const char *XException::what() const noexcept {
    return description.c_str();
}
