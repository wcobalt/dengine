//
// Created by wcobalt on 19.09.18.
//

#include "Component.h"

using namespace dengine::components;

Component::Component(const std::string& id):id(id) {
    mIsOnly = true;
    mIsEnabled = true;
}

bool Component::isOnly() const {
    return mIsOnly;
}

void Component::setOnly(bool isOnly) {
    Component::mIsOnly = isOnly;
}

bool Component::isEnabled() const {
    return mIsEnabled;
}

void Component::setEnabled(bool isEnabled) {
    Component::mIsEnabled = isEnabled;
}

const std::string& Component::getID() const {
    return id;
}