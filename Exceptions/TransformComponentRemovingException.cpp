//
// Created by wcobalt on 4/6/19.
//

#include "TransformComponentRemovingException.h"

using namespace dengine::exceptions;

const char* TransformComponentRemovingException::what() const noexcept {
    return "You can't remove components inherited from Transform3DComponent";
}