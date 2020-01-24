//
// Created by wcobalt on 1/23/20.
//

#include "BaseTraversal.h"

using namespace dengine;

BaseTraversal::BaseTraversal() : mIsStopped(false) {}

void BaseTraversal::setStopped(bool isStopped) {
    mIsStopped = isStopped;
}

bool BaseTraversal::isStopped() const {
    return mIsStopped;
}
