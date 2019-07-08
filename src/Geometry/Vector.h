//
// Created by wcobalt on 23.05.19.
//

#include <vector>

#ifndef DENGINE_VECTOR_H
#define DENGINE_VECTOR_H

#include "../DObject.h"

namespace dengine::geometry {
    template <class T>
    class Vector : public DObject {
    public:
        virtual T getModule() const = 0;

        virtual void normalize() = 0;

        virtual Vector<T> getNormalizedVector() const = 0;

        virtual std::vector<T> getstl() const = 0;
    };
}

#endif //DENGINE_VECTOR_H
