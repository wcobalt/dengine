//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_NOCURRENTSCENEEXCEPTION_H
#define DENGINE_NOCURRENTSCENEEXCEPTION_H

#include "DengineException.h"

namespace dengine::exceptions {
    class NoCurrentSceneException : public DengineException {
        const char* what() const noexcept;
    };
}


#endif //DENGINE_NOCURRENTSCENEEXCEPTION_H
