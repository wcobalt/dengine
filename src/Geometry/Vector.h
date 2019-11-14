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
        static const double constexpr AUTO_ANGLE_CALC_PRECISION = 10e-6;

        virtual T getModulo() const = 0;

        virtual void normalize() = 0;

        virtual std::vector<T> toStlVector() const = 0;
    };

    template<typename T>
    const double Vector<T>::AUTO_ANGLE_CALC_PRECISION;
}

#endif //DENGINE_VECTOR_H
