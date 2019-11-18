//
// Created by wcobalt on 3/30/19.
//
#include <memory>

#include "Component.h"
#include "../GameObject.h"
#include "../Exceptions/ComponentException.h"
#include "../Exceptions/IllegalArgumentException.h"

using namespace dengine;

Component::Component(std::shared_ptr<GameObject> gameObject) {
    if (gameObject == nullptr) throw IllegalArgumentException("Game object cannot be null");

    this->gameObject = gameObject;
}

void Component::onInstanceCreate() {}

void Component::onComponentLoad() {}

void Component::onComponentUnload() {}

void Component::onUpdate(std::shared_ptr<EventsState> eventsState) {}

void Component::onInstanceDestroy() {}

void Component::onSceneUnload() {}

void Component::onGameEnd() {}

void Component::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

bool Component::isEnabled() const {
    return mIsEnabled;
}

std::shared_ptr<GameObject> Component::getGameObject() const {
    return gameObject;
}
