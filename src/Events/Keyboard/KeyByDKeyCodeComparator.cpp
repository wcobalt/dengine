//
// Created by wcobalt on 5/31/19.
//
#include <memory>

#include "KeyByDKeyCodeComparator.h"
#include "KeyCode.h"
#include "Key.h"

using namespace dengine::events::keyboard;

bool KeyByDKeyCodeComparator::operator()(const std::shared_ptr<Key> &a,
                                         const std::shared_ptr<Key> &b) const {

    return a->getKeycode() > b->getKeycode();
}