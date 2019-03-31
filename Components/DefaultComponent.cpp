//
// Created by wcobalt on 3/30/19.
//

#include "DefaultComponent.h"
#include "../Exceptions/ComponentIsNotBoundException.h"

using namespace dengine;
using namespace dengine::components;
using namespace dengine::exceptions;

DefaultComponent::DefaultComponent() = default;

void DefaultComponent::componentUnload() {}

void DefaultComponent::update() {}

void DefaultComponent::instanceCreate() {}

void DefaultComponent::instanceDestroy() {}

void DefaultComponent::sceneUnload() {}

void DefaultComponent::componentLoad(shared_ptr<GameObject> instance) {
    boundInstance = instance;
}

void DefaultComponent::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

bool DefaultComponent::isEnabled() const {
    return mIsEnabled;
}

shared_ptr<GameObject> DefaultComponent::getBoundInstance() const {
    if (boundInstance != nullptr)
        return boundInstance;

    throw ComponentIsNotBoundException();
}