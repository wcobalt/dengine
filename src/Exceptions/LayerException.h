//
// Created by wcobalt on 11/21/19.
//

#ifndef DENGINE_LAYEREXCEPTION_H
#define DENGINE_LAYEREXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class LayerException : public DengineException {
    public:
        LayerException(const std::string &message) : DengineException(message) {}
    };
}

#endif //DENGINE_LAYEREXCEPTION_H
