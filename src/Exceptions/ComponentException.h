//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_NOCASTTOCOMPONENTEXCEPTION_H
#define DENGINE_NOCASTTOCOMPONENTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class ComponentException : public DengineException {
    public:
        ComponentException(const std::string& message) : DengineException(message) {}
    };
}

#endif //DENGINE_NOCASTTOCOMPONENTEXCEPTION_H
