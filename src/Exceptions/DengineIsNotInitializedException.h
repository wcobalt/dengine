//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_DENGINEISNOTINITIALIZEDYET_H
#define DENGINE_DENGINEISNOTINITIALIZEDYET_H

#include "DengineException.h"

namespace dengine::exceptions {
    class DengineIsNotInitializedException : public DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_DENGINEISNOTINITIALIZEDYET_H