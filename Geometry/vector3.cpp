//
// Created by wcobalt on 3/23/19.
//

#include "vector3.h"
#include <cmath>

using namespace dengine::geometry;

template<class T>
vector3<T>::vector3() {
    x = y = z = (T)0;
}

template<class T>
vector3<T>::vector3(vector3<T> &vec) {
    *this = vec;
}

template<class T>
vector3<T>::vector3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<class T>
T vector3<T>::getModule() {
    return (T)std::sqrt(x * x + y * y + z * z);
}

template<class T>
void vector3<T>::normalize() {
    T module = getModule();

    x /= module;
    y /= module;
    z /= module;
}

template<class T>
vector3<T> vector3<T>::getNormalizedVector() {
    vector3<T> result(*this);

    result.normalize();

    return result;
}

template<class T>
vector3<T>& vector3<T>::operator=(vector3<T> b) {
    x = b.x;
    y = b.y;
    z = b.z;

    return *this;
}

template<class T>
vector3<T> vector3<T>::operator+=(vector3<T> b) {
    return *this + b;
}

template<class T>
vector3<T> vector3<T>::operator+(vector3<T> b) {
    vector3<T> result(*this);

    result.x += b.x;
    result.y += b.y;
    result.z += b.z;

    return result;
}

template<class T>
vector3<T> vector3<T>::operator-=(vector3<T> b) {
    return *this - b;
}

template<class T>
vector3<T> vector3<T>::operator-(vector3<T> b) {
    vector3<T> result(*this);

    result.x -= b.x;
    result.y -= b.y;
    result.z -= b.z;

    return result;
}

template<class T>
vector3<T> vector3<T>::operator-() {
    vector3<T> result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}