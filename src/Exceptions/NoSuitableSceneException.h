//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_NOSUITABLESCENEEXCEPTION_H
#define DENGINE_NOSUITABLESCENEEXCEPTION_H

#include "DengineException.h"

namespace dengine::exceptions {
    class NoSuitableSceneException : public DengineException {
        const char* what() const noexcept;
    };
}


#endif //DENGINE_NOSUITABLESCENEEXCEPTION_H
