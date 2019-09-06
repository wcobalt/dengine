//
// Created by wcobalt on 02.09.19.
//

#include "DengineException.h"

using namespace dengine::exceptions;

DengineException::DengineException(const std::string &message):message(message) {}

const char *DengineException::what() const noexcept {
    return message.c_str();
}

