//
// Created by wcobalt on 3/31/19.
//

#ifndef DENGINE_NOSUITABLECOMPONENTEXCEPTION_H
#define DENGINE_NOSUITABLECOMPONENTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class NoSuitableComponentException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_NOSUITABLECOMPONENTEXCEPTION_H
