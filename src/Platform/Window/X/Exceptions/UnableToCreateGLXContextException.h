//
// Created by wcobalt on 6/1/19.
//

#ifndef DENGINE_UNABLETOCREATEGLXCONTEXTEXCEPTION_H
#define DENGINE_UNABLETOCREATEGLXCONTEXTEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine::platform::window::x::exceptions {
    class UnableToCreateGLXContextException : public dengine::exceptions::DengineException {
        const char* what() const noexcept;
    };
}


#endif //DENGINE_UNABLETOCREATEGLXCONTEXTEXCEPTION_H
