//
// Created by wcobalt on 1/23/20.
//

#include "BaseTraversal.h"

using namespace dengine;

BaseTraversal::BaseTraversal(const Filter &filter) : filter(filter), mIsStopped(false) {}

void BaseTraversal::stop() {
    mIsStopped = true;
}

bool BaseTraversal::isStopped() const {
    return mIsStopped;
}
