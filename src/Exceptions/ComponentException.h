//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_COMPONENTEXCEPTION_H
#define DENGINE_COMPONENTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class ComponentException : public DengineException {
    public:
        ComponentException(std::string message) : DengineException(std::move(message)) {}
    };
}

#endif //DENGINE_COMPONENTEXCEPTION_H
