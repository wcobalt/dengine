//
// Created by wcobalt on 11/7/19.
//

#ifndef DENGINE_IMAGEEXCEPTION_H
#define DENGINE_IMAGEEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class ImageException : public DengineException {
    public:
        ImageException(std::string message) : DengineException(std::move(message)) {}
    };
}

#endif //DENGINE_IMAGEEXCEPTION_H
