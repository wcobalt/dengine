//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_PLATFORMBUILDEXCEPTION_H
#define DENGINE_PLATFORMBUILDEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class PlatformBuildException : public DengineException {
    public:
        explicit PlatformBuildException(std::string message) : DengineException(std::move(message)) {}
    };
}

#endif //DENGINE_PLATFORMBUILDEXCEPTION_H
