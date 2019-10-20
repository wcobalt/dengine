//
// Created by wcobalt on 10/20/19.
//

#ifndef DENGINE_ZLIBEXCEPTION_H
#define DENGINE_ZLIBEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine {
    class ZlibException : public DengineException {
    public:
        ZlibException(const std::string& message);
    };
}

#endif //DENGINE_ZLIBEXCEPTION_H
