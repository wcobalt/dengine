//
// Created by wcobalt on 11/20/19.
//
#include <memory>

#ifndef DENGINE_INITIALIZER_H
#define DENGINE_INITIALIZER_H

namespace dengine {
    class GameObject;
}

namespace dengine {
    class Initializer {
    public:
        virtual void initialize(GameObject &gameObject) {};
    };
}

#endif //DENGINE_INITIALIZER_H
