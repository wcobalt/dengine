//
// Created by wcobalt on 3/23/19.
//

#include "NoSuitableSceneException.h"

using namespace dengine::exceptions;

const char* NoSuitableSceneException::what() const noexcept {
    return "There is no scene with that id";
}