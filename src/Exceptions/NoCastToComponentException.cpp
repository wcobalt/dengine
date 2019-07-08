//
// Created by wcobalt on 4/6/19.
//

#include "NoCastToComponentException.h"

using namespace dengine::exceptions;

const char* NoCastToComponentException::what() const noexcept {
    return "No viable cast from your type to Component.";
}