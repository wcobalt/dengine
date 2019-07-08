//
// Created by wcobalt on 3/31/19.
//

#include "NoSuitableComponentException.h"

using namespace dengine::exceptions;

const char* NoSuitableComponentException::what() const noexcept {
    return "Required Component not found. Have you add this to GameObject?";
}