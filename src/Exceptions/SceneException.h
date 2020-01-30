//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_NOSUITABLESCENEEXCEPTION_H
#define DENGINE_NOSUITABLESCENEEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class SceneException : public DengineException {
    public:
        SceneException(std::string message) : DengineException(std::move(message)) {}
    };
}


#endif //DENGINE_NOSUITABLESCENEEXCEPTION_H
