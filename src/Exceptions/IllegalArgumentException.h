//
// Created by wcobalt on 10/15/19.
//
#include <string>

#ifndef DENGINE_ILLEGALARGUMENTEXCEPTION_H
#define DENGINE_ILLEGALARGUMENTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class IllegalArgumentException : public DengineException {
    public:
        IllegalArgumentException(const std::string& message) : DengineException(message) {}
    };
}


#endif //DENGINE_ILLEGALARGUMENTEXCEPTION_H
