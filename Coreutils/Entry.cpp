//
// Created by wcobalt on 3/23/19.
//

#include "Entry.h"
using namespace dengine::coreutils;

template <class T>
Entry<T>::Entry(std::shared_ptr<T> object, ulong id) {
    this->object = object;
    this->id = id;
}

template <class T>
std::shared_ptr<T> Entry<T>::getObject() {
    return object;
}

template <class T>
ulong Entry<T>::getId() {
    return id;
}