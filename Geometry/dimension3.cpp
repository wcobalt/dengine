//
// Created by wcobalt on 3/26/19.
//

#include "dimension3.h"

using namespace dengine::geometry;

template<class T>
dimension3<T>::dimension3() {
    width =  height =  depth = (T)0;
}

template<class T>
dimension3<T>::dimension3(vector3<T> vec) {
    width = vec.x;
    height = vec.y;
    depth = vec.z;
}

template<class T>
dimension3<T>::dimension3(const dimension3<T> &dimension) {
    width = dimension.width;
    height = dimension.height;
    depth = dimension.depth;
}

template<class T>
dimension3<T>::dimension3(T width, T height, T depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
}