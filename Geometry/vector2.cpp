//
// Created by wcobalt on 3/23/19.
//

#include "vector2.h"

using namespace dengine::geometry;

template<class T>
vector2<T>::vector2():vector3<T>() {}

template<class T>
vector2<T>::vector2(vector2<T> &vec):vector3<T>(vec) {
    vector3<T>::z = 0;
}

template<class T>
vector2<T>::vector2(T x, T y):vector3<T>(x, y, 0) {

}

template<class T>
vector2<T> vector2<T>::getNormalizedVector() {
    vector2<T> result(*this);

    result.normalize();

    return result;
}

template<class T>
vector2<T>& vector2<T>::operator=(vector2<T> b) {
    vector3<T>::x = b.x;
    vector3<T>::y = b.y;
}

template<class T>
vector2<T> vector2<T>::operator+(vector2<T> b) {
    vector2<T> result(*this);

    result.x += b.x;
    result.y += b.y;

    return result;
}

template<class T>
vector2<T> vector2<T>::operator-(vector2<T> b) {
    vector2<T> result(*this);

    result.x -= b.x;
    result.y -= b.y;

    return result;
}

template<class T>
vector2<T> vector2<T>::operator-() {
    vector2<T> result(*this);

    result.x = -vector3<T>::x;
    result.y = -vector3<T>::y;

    return result;
}