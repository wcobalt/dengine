//
// Created by wcobalt on 5/31/19.
//

#ifndef DENGINE_NOSUITABLEXVISUALINFOEXCEPTION_H
#define DENGINE_NOSUITABLEXVISUALINFOEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine::platform::window::x::exceptions {
    class NoSuitableXVisualInfoException : public dengine::exceptions::DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_NOSUITABLEXVISUALINFOEXCEPTION_H
