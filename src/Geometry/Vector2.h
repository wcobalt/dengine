//
// Created by wcobalt on 3/23/19.
//

#include <vector>

#ifndef DENGINE_VECTOR2_H
#define DENGINE_VECTOR2_H

namespace dengine {
    template <class T> class Vector3;
}

#include "Vector.h"

namespace dengine {
    template <class T>
    class Vector2 : public Vector<T> {
    public:
        T x, y;

        Vector2();
        Vector2(const Vector2<T>& vector);
        Vector2(const Vector3<T>& vector);
        Vector2(T x, T y);
        Vector2(const std::vector<T>& vector);

        T getModule() const;

        void normalize();

        Vector2<T> getNormalizedVector() const;

        std::vector<T> getstl() const;

        Vector2<T>& operator=(const Vector2<T>& b);
        Vector2<T>& operator+=(const Vector2<T>& b);
        Vector2<T> operator+(const Vector2<T>& b) const;
        Vector2<T>& operator-=(const Vector2<T>& b);
        Vector2<T> operator-(const Vector2<T>& b) const;
        Vector2<T> operator-() const;
        Vector2<T>& operator*=(T b);
        Vector2<T> operator*(T b) const;
        Vector2<T>& operator/=(T b);
        Vector2<T> operator/(T b) const;
    };
}

#endif //DENGINE_VECTOR2_H
