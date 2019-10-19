//
// Created by wcobalt on 10/15/19.
//
#include <string>

#ifndef DENGINE_INVALIDSTATEEXCEPTION_H
#define DENGINE_INVALIDSTATEEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class InvalidStateException : public DengineException {
    public:
        InvalidStateException(const std::string& message);
    };
}


#endif //DENGINE_INVALIDSTATEEXCEPTION_H
