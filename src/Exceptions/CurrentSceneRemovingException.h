//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_CURRENTSCENEREMOVINGEXCEPTION_H
#define DENGINE_CURRENTSCENEREMOVINGEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class CurrentSceneRemovingException : public DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_CURRENTSCENEREMOVINGEXCEPTION_H
