//
// Created by wcobalt on 3/23/19.
//

#include <vector>

#ifndef DENGINE_VECTOR3_H
#define DENGINE_VECTOR3_H

namespace dengine {
    template <class T> class Vector2;
}

#include "Vector.h"

namespace dengine {
    template<typename T>
    class Vector3 : public Vector<T> {
    public:
        T x, y, z;

        Vector3();
        Vector3(const Vector3<T>& vector);
        Vector3(const Vector2<T>& vector);
        Vector3(T x, T y, T z);
        Vector3(const std::vector<T>& vector);

        T getModule() const;

        void normalize();

        Vector3<T> getNormalizedVector() const;

        std::vector<T> getstl() const;

        Vector3<T>& operator=(const Vector3<T>& b);
        Vector3<T>& operator+=(const Vector3<T>& b);
        Vector3<T> operator+(const Vector3<T>& b) const;
        Vector3<T>& operator-=(const Vector3<T>& b);
        Vector3<T> operator-(const Vector3<T>& b) const;
        Vector3<T>& operator*=(T b);
        Vector3<T> operator*(T b) const;
        Vector3<T>& operator/=(T b);
        Vector3<T> operator/(T b) const;
        Vector3<T> operator-();
    };
}

#endif //DENGINE_VECTOR3_H
