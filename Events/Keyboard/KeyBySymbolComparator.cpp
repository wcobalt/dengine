//
// Created by wcobalt on 5/31/19.
//

#include "KeyBySymbolComparator.h"

using std::string;

using namespace dengine::events::keyboard;

bool KeyBySymbolComparator::operator()(const string &a, const string &b) const {
    return a > b;
}