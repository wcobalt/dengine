//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_NOCASTTOCOMPONENTEXCEPTION_H
#define DENGINE_NOCASTTOCOMPONENTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class NoCastToComponentException : public DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_NOCASTTOCOMPONENTEXCEPTION_H
