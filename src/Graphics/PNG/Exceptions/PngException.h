//
// Created by wcobalt on 10/27/19.
//

#ifndef DENGINE_PNGEXCEPTION_H
#define DENGINE_PNGEXCEPTION_H

#include "../../../Exceptions/DengineException.h"

namespace dengine {
    class PngException : public DengineException {
    public:
        PngException(const std::string &message);
    };
}

#endif //DENGINE_PNGEXCEPTION_H
