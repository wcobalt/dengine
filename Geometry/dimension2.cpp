//
// Created by wcobalt on 3/26/19.
//

#include "dimension2.h"
#include "dimension3.h"
#include "vector2.h"

using namespace dengine::geometry;

template<class T>
dimension2<T>::dimension2():dimension3<T>() {}

template<class T>
dimension2<T>::dimension2(vector2<T> vec):dimension3<T>(vec) {}

template<class T>
dimension2<T>::dimension2(const dimension2<T> &dimension):dimension2<T>(dimension) {}

template <class T>
dimension2<T>::dimension2(const dimension3<T> &dimension):dimension3<T>(dimension) {
    dimension3<T>::depth = (T)0;
}

template<class T>
dimension2<T>::dimension2(T width, T height):dimension3<T>(width, height, (T)0) {}