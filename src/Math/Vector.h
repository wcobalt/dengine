//
// Created by wcobalt on 23.05.19.
//

#include <vector>

#ifndef DENGINE_VECTOR_H
#define DENGINE_VECTOR_H

#include "../DObject.h"

namespace dengine {
    template <typename T>
    class Vector : public DObject {
    public:
        virtual T getModulo() const = 0;

        virtual void normalize() = 0;

        virtual std::vector<T> toStlVector() const = 0;
    };
}

#endif //DENGINE_VECTOR_H
