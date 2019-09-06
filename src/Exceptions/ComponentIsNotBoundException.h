//
// Created by wcobalt on 3/31/19.
//

#ifndef DENGINE_COMPONENTISNOTATTACHEDEXCEPTION_H
#define DENGINE_COMPONENTISNOTATTACHEDEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class ComponentIsNotBoundException : public DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_COMPONENTISNOTATTACHEDEXCEPTION_H
