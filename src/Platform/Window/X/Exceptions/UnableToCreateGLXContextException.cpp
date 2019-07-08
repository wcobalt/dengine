//
// Created by wcobalt on 6/1/19.
//

#include "UnableToCreateGLXContextException.h"

using namespace dengine::platform::window::x::exceptions;

const char* UnableToCreateGLXContextException::what() const noexcept {
    return "Unable to create GLXContext";
}