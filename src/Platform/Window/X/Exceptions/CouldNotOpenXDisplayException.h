//
// Created by wcobalt on 5/31/19.
//

#ifndef DENGINE_COULDNOTOPENXDISPLAYEXCEPTION_H
#define DENGINE_COULDNOTOPENXDISPLAYEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine::platform::window::x::exceptions {
    class CouldNotOpenXDisplayException : public dengine::exceptions::DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_COULDNOTOPENXDISPLAYEXCEPTION_H
