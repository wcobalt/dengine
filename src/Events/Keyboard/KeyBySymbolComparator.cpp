//
// Created by wcobalt on 5/31/19.
//
#include <memory>
#include <string>

#include "KeyBySymbolComparator.h"
#include "Key.h"

using std::string;

using namespace dengine::events::keyboard;

bool KeyBySymbolComparator::operator()(const std::shared_ptr<Key> &a,
                                       const std::shared_ptr<Key> &b) const {
    return a->getSymbol() > b->getSymbol();
}