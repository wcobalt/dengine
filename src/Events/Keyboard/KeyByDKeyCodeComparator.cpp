//
// Created by wcobalt on 5/31/19.
//
#include <memory>

#include "KeyByDKeyCodeComparator.h"
#include "Keyboard.h"
#include "Key.h"

using namespace dengine;

bool KeyByDKeyCodeComparator::operator()(const std::shared_ptr<Key> &a,
                                         const std::shared_ptr<Key> &b) const {

    return a->getKeycode() > b->getKeycode();
}