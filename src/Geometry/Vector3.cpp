//
// Created by wcobalt on 3/23/19.
//

#include <cmath>
#include <vector>

#include "Vector3.h"
#include "Vector2.h"
#include "../Exceptions/LessThanVectorException.h"

using std::vector;

using namespace dengine::exceptions;
using namespace dengine::geometry;

template <class T>
Vector3<T>::Vector3():x((T)0), y((T)0), z((T)0) {}

template <class T>
Vector3<T>::Vector3(const Vector3<T> &vector) = default;

template <class T>
Vector3<T>::Vector3(const Vector2<T> &vector):x(vector.x), y(vector.y), z((T)0) {}

template <class T>
Vector3<T>::Vector3(T x, T y, T z):x(x), y(y), z(z) {}

template <class T>
Vector3<T>::Vector3(const std::vector<T> &vector) {
    if (vector.size() >= 3) {
        x = vector[0];
        y = vector[1];
        z = vector[2];
    } else
        throw LessThanVectorException(3);
}

template <class T>
T Vector3<T>::getModule() const {
    return (T)std::sqrt(x * x + y * y + z * z);
}

template <class T>
void Vector3<T>::normalize() {
    T module = getModule();

    *this /= module;
}

template <class T>
Vector3<T> Vector3<T>::getNormalizedVector() const {
    Vector3<T> result(*this);

    result.normalize();

    return result;
}

template <class T>
vector<T> Vector3<T>::getstl() const {
    return {x, y, z};
}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& b) = default;

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& b) {
    return *this = *this + b;
}

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& b) const {
    Vector3<T> result(*this);

    result.x += b.x;
    result.y += b.y;
    result.z += b.z;

    return result;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& b) {
    return *this = *this - b;
}

template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& b) const {
    Vector3<T> result(*this);

    result.x -= b.x;
    result.y -= b.y;
    result.z -= b.z;

    return result;
}

template <class T>
Vector3<T> Vector3<T>::operator-() {
    Vector3<T> result;

    result *= (T)-1;

    return result;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(T b) {
    return *this = *this * b;
}

template <class T>
Vector3<T> Vector3<T>::operator*(T b) const {
    Vector3<T> result(*this);

    result.x *= b;
    result.y *= b;
    result.z *= b;

    return result;
}

template <class T>
Vector3<T>& Vector3<T>::operator/=(T b) {
    return *this = *this / b;
}

template <class T>
Vector3<T> Vector3<T>::operator/(T b) const {
    Vector3<T> result(*this);

    result.x /= b;
    result.y /= b;
    result.z /= b;

    return result;
}