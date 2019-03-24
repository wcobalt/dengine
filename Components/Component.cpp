//
// Created by wcobalt on 19.09.18.
//

#include "Component.h"

using namespace dengine::components;

Component::Component() = default;

bool Component::isEnabled() const {
    return mIsEnabled;
}

void Component::setEnabled(bool isEnabled) {
    Component::mIsEnabled = isEnabled;
}