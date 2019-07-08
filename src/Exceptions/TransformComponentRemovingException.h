//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_TRANSFORMCOMPONENTREMOVINGEXCEPTION_H
#define DENGINE_TRANSFORMCOMPONENTREMOVINGEXCEPTION_H

#include "DengineException.h"

namespace dengine::exceptions {
    class TransformComponentRemovingException : public DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_TRANSFORMCOMPONENTREMOVINGEXCEPTION_H
