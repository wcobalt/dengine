//
// Created by wcobalt on 3/23/19.
//

#include "CurrentSceneRemovingException.h"

using namespace dengine;

const char* CurrentSceneRemovingException::what() const noexcept {
    return "You cannot remove current scene";
}