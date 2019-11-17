//
// Created by wcobalt on 3/30/19.
//
#include <memory>

#include "BaseComponent.h"
#include "../DengineAccessor.h"
#include "../GameObject.h"
#include "../Exceptions/ComponentException.h"

using namespace dengine;

void BaseComponent::componentUnload(const DengineAccessor& dengineAccessor) {}

void BaseComponent::update(const DengineAccessor& dengineAccessor) {}

void BaseComponent::instanceCreate(const DengineAccessor& dengineAccessor) {}

void BaseComponent::instanceDestroy(const DengineAccessor& dengineAccessor) {}

void BaseComponent::sceneUnload(const DengineAccessor& dengineAccessor) {}

void BaseComponent::componentLoad(const DengineAccessor& dengineAccessor, std::shared_ptr<GameObject> instance) {
    boundInstance = instance;
}

void BaseComponent::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

bool BaseComponent::isEnabled() const {
    return mIsEnabled;
}

std::shared_ptr<GameObject> BaseComponent::getBoundInstance() const {
    if (boundInstance != nullptr)
        return boundInstance;

    throw ComponentException("The component is not bound yet");
}