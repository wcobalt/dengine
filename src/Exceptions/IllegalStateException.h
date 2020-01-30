//
// Created by wcobalt on 10/15/19.
//
#include <string>

#ifndef DENGINE_INVALIDSTATEEXCEPTION_H
#define DENGINE_INVALIDSTATEEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class IllegalStateException : public DengineException {
    public:
        IllegalStateException(std::string message) : DengineException(std::move(message)) {}
    };
}


#endif //DENGINE_INVALIDSTATEEXCEPTION_H
