//
// Created by wcobalt on 4/6/19.
//

#include "ComponentAlreadyAddedException.h"

using namespace dengine;

const char* ComponentAlreadyAddedException::what() const noexcept {
    return "Component what you try to add already added to the GameObject.";
}