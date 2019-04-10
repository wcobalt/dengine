//
// Created by wcobalt on 3/30/19.
//

#include "DefaultComponent.h"
#include "../Exceptions/ComponentIsNotBoundException.h"

using namespace dengine;
using namespace dengine::components;
using namespace dengine::exceptions;

DefaultComponent::DefaultComponent() = default;

void DefaultComponent::componentUnload(DengineAccessor dengineAccessor) {}

void DefaultComponent::update(DengineAccessor dengineAccessor) {}

void DefaultComponent::instanceCreate(DengineAccessor dengineAccessor) {}

void DefaultComponent::instanceDestroy(DengineAccessor dengineAccessor) {}

void DefaultComponent::sceneUnload(DengineAccessor dengineAccessor) {}

void DefaultComponent::componentLoad(DengineAccessor dengineAccessor, shared_ptr<GameObject> instance) {
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