//
// Created by wcobalt on 3/23/19.
//

#include "Entry.h"

using namespace dengine;
using namespace dengine::coreutils;

template <class T>
Entry<T>::Entry(std::shared_ptr<T> object, ID id) {
    this->object = object;
    this->id = id;
}

template <class T>
std::shared_ptr<T> Entry<T>::getObject() {
    return object;
}

template <class T>
ID Entry<T>::getID() {
    return id;
}