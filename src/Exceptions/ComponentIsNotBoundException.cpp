//
// Created by wcobalt on 3/31/19.
//

#include "ComponentIsNotBoundException.h"

using namespace dengine::exceptions;

const char* ComponentIsNotBoundException::what() const noexcept {
    return "This Component is not attached to any GameObject yet. Call GameObject::addComponent().";
}