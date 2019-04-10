//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_COMPONENTALREADYEXISTEXCEPTION_H
#define DENGINE_COMPONENTALREADYEXISTEXCEPTION_H

#include "DengineException.h"

namespace dengine::exceptions {
    class ComponentAlreadyAddedException : public DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_COMPONENTALREADYEXISTEXCEPTION_H
