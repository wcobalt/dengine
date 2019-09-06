//
// Created by wcobalt on 3/23/19.
//

#include <cmath>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "../Exceptions/LessThanVectorException.h"

using std::vector;

using namespace dengine;

//there are partly duplicated constructors. dupl-n is made for optimization
template <class T>
Vector2<T>::Vector2():x((T)0), y((T)0) {}

template <class T>
Vector2<T>::Vector2(const Vector2<T> &vector) = default;

template <class T>
Vector2<T>::Vector2(const Vector3<T> &vector):x(vector.x), y(vector.y) {}

template <class T>
Vector2<T>::Vector2(T x, T y):x(x), y(y) {}

template <class T>
Vector2<T>::Vector2(const std::vector<T> &vector) {
    if (vector.size() >= 2) {
        x = vector[0];
        y = vector[1];
    } else
        throw LessThanVectorException(2);
}

template <class T>
T Vector2<T>::getModule() const {
    return sqrt(x * x + y * y);
}

template <class T>
void Vector2<T>::normalize() {
    T module = getModule();

    *this /= module;
}

template <class T>
Vector2<T> Vector2<T>::getNormalizedVector() const {
    Vector2<T> result(*this);

    result.normalize();

    return result;
}

template <class T>
std::vector<T> Vector2<T>::getstl() const {
    return {x, y};
}

template <class T>
Vector2<T>& Vector2<T>::operator=(const Vector2<T>& b) = default;

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& b) {
    return *this = *this + b;
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& b) const {
    Vector2<T> result(*this);

    result.x += b.x;
    result.y += b.y;

    return result;
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& b) {
    return *this = *this - b;
}

template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& b) const {
    Vector2<T> result(*this);

    result.x -= b.x;
    result.y -= b.y;

    return result;
}

template <class T>
Vector2<T> Vector2<T>::operator-() const {
    Vector2<T> result(*this);

    result *= (T)-1;

    return result;
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(T b) {
    return *this = *this * b;
}

template <class T>
Vector2<T> Vector2<T>::operator*(T b) const {
    Vector2<T> result(*this);

    result.x *= b;
    result.y *= b;

    return result;
}

template <class T>
Vector2<T>& Vector2<T>::operator/=(T b) {
    return *this = *this / b;
}

template <class T>
Vector2<T> Vector2<T>::operator/(T b) const {
    Vector2<T> result(*this);

    result.x /= b;
    result.y /= b;

    return result;
}