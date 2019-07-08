//
// Created by wcobalt on 3/23/19.
//

#include "NoCurrentSceneException.h"

using namespace dengine::exceptions;

const char* NoCurrentSceneException::what() const noexcept {
    return "Current scene is not defined";
}