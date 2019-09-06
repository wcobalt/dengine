//
// Created by wcobalt on 3/30/19.
//
#include <memory>

#include "DefaultComponent.h"
#include "../DengineAccessor.h"
#include "../GameObject.h"
#include "../Exceptions/ComponentIsNotBoundException.h"

using namespace dengine;

using std::shared_ptr;

DefaultComponent::DefaultComponent() = default;

void DefaultComponent::componentUnload(const DengineAccessor& dengineAccessor) {}

void DefaultComponent::update(const DengineAccessor& dengineAccessor) {}

void DefaultComponent::instanceCreate(const DengineAccessor& dengineAccessor) {}

void DefaultComponent::instanceDestroy(const DengineAccessor& dengineAccessor) {}

void DefaultComponent::sceneUnload(const DengineAccessor& dengineAccessor) {}

void DefaultComponent::componentLoad(const DengineAccessor& dengineAccessor, shared_ptr<GameObject> instance) {
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