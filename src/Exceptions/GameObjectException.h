//
// Created by wcobalt on 11/20/19.
//

#ifndef DENGINE_GAMEOBJECTEXCEPTION_H
#define DENGINE_GAMEOBJECTEXCEPTION_H

#include "DengineException.h"

namespace dengine {
    class GameObjectException : public DengineException {
    public:
        GameObjectException(std::string message) : DengineException(std::move(message)) {}
    };
}

#endif //DENGINE_GAMEOBJECTEXCEPTION_H
