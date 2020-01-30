//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_SPACEEXCEPTION_H
#define DENGINE_SPACEEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class SpaceException : public DengineException {
    public:
        explicit SpaceException(std::string message) : DengineException(std::move(message)) {}
    };
}

#endif //DENGINE_SPACEEXCEPTION_H
