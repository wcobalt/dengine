//
// Created by wcobalt on 02.09.19.
//

#include <string>

#ifndef DENGINE_IOEXCEPTION_H
#define DENGINE_IOEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class IOException : public DengineException {
    public:
        IOException(std::string message) : DengineException(std::move(message)) {}
    };
}

#endif //DENGINE_IOEXCEPTION_H
