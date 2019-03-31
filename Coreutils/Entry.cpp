//
// Created by wcobalt on 3/23/19.
//

#include "Entry.h"

using namespace dengine;
using namespace dengine::coreutils;

template <class K, class V>
Entry<K, V>::Entry(K id, std::shared_ptr<V> object) {
    this->object = object;
    this->id = id;
}

template <class K, class V>
std::shared_ptr<V> Entry<K, V>::getObject() const {
    return object;
}

template <class K, class V>
K Entry<K, V>::getID() const {
    return id;
}