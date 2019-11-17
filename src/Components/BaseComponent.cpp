//
// Created by wcobalt on 3/30/19.
//
#include <memory>

#include "BaseComponent.h"
#include "../GameObject.h"
#include "../Exceptions/ComponentException.h"

using namespace dengine;

void BaseComponent::componentUnload() {}

void BaseComponent::update() {}

void BaseComponent::instanceCreate() {}

void BaseComponent::instanceDestroy() {}

void BaseComponent::sceneUnload() {}

void BaseComponent::componentLoad(std::shared_ptr<GameObject> instance) {
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