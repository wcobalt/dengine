//
// Created by wcobalt on 10/15/19.
//
#include <string>

#ifndef DENGINE_INVALIDARGUMENTEXCEPTION_H
#define DENGINE_INVALIDARGUMENTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class InvalidArgumentException : public DengineException {
    public:
        InvalidArgumentException(const std::string& message);
    };
}


#endif //DENGINE_INVALIDARGUMENTEXCEPTION_H
