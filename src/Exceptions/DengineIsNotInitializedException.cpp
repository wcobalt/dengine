//
// Created by wcobalt on 3/30/19.
//

#include "DengineIsNotInitializedException.h"

using namespace dengine::exceptions;

const char* DengineIsNotInitializedException::what() const noexcept {
    return "The engine was not initialized yet. Call Dengine::init() before calling Dengine::get().";
}