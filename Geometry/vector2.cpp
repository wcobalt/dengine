//
// Created by wcobalt on 3/23/19.
//

#include "vector2.h"

using namespace dengine::geometry;

template<class T>
vector2<T>::vector2():vector3<T>() {}

template<class T>
vector2<T>::vector2(const vector2<T> &vec):vector2<T>(vec) {}

template <class T>
vector2<T>::vector2(const vector3<T> &vec):vector3<T>(vec) {
    vector3<T>::z = (T)0;
}

template<class T>
vector2<T>::vector2(T x, T y):vector3<T>(x, y, (T)0) {}

template<class T>
vector2<T>& vector2<T>::operator=(const vector2<T>& b) {
    (vector3<T>)*this = b;

    return *this;
}

template<class T>
vector2<T> vector2<T>::operator+=(dengine::geometry::vector2<T> b) {
    return *this + b;
}

template<class T>
vector2<T> vector2<T>::operator+(vector2<T> b) {
    vector3<T> a(*this);

    a += b;

    vector2<T> result(a);

    return result;
}

template<class T>
vector2<T> vector2<T>::operator-=(dengine::geometry::vector2<T> b) {
    return *this - b;
}

template<class T>
vector2<T> vector2<T>::operator-(vector2<T> b) {
    vector3<T> a(*this);

    a -= b;

    vector2<T> result(a);

    return result;
}