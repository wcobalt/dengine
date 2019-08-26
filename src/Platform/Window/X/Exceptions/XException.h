//
// Created by wcobalt on 22.08.19.
//

#include <string>

#ifndef DENGINE_XEXCEPTION_H
#define DENGINE_XEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine::platform::window::x::exceptions {
class XException : public dengine::exceptions::DengineException {
    private:
        std::string description;
    public:
        XException(const std::string& description);

        virtual const char* what() const noexcept;
    };
}

#endif //DENGINE_XEXCEPTION_H
