//
// Created by wcobalt on 10/17/19.
//
#include <string>

#ifndef DENGINE_DEFLATEEXCEPTION_H
#define DENGINE_DEFLATEEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine {
    class DeflateException : public DengineException {
    public:
        DeflateException(const std::string& message);
    };
}

#endif //DENGINE_DEFLATEEXCEPTION_H
