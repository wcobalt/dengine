//
// Created by wcobalt on 22.08.19.
//

#include <string>

#ifndef DENGINE_XEXCEPTION_H
#define DENGINE_XEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine {
class XException : public dengine::DengineException {
    public:
        XException(const std::string& message) : DengineException(message) {}
    };
}

#endif //DENGINE_XEXCEPTION_H
