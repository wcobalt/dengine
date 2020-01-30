//
// Created by wcobalt on 3/30/19.
//
#include <memory>

#include "Component.h"
#include "../Dengine.h"
#include "../GameObject.h"
#include "../ScenesManager.h"
#include "../Exceptions/ComponentException.h"
#include "../Exceptions/IllegalArgumentException.h"
#include "../Coreutils/Messages/ParentChangeMessage.h"
#include "../Coreutils/Messages/DirectChildrenChangeMessage.h"
#include "../Coreutils/Messages/ComponentMessage.h"

using namespace dengine;

Component::Component(GameObject &gameObject) : gameObject(gameObject) {}

void Component::onInstanceCreate(const InstanceCreateMessage &message) {}

void Component::onComponentLoad(const ComponentLoadMessage &message) {}

void Component::onComponentUnload(const ComponentUnloadMessage &message) {}

void Component::onUpdate(const UpdateMessage &message) {}

void Component::onInstanceDestroy(const InstanceDestroyMessage &message) {}

void Component::onSceneUnload(const SceneUnloadMessage &message) {}

void Component::onGameEnd(const GameEndMessage &message) {}

void Component::onDirectChildrenChange(const DirectChildrenChangeMessage &message) {}

void Component::onParentChange(const ParentChangeMessage &message) {}

void Component::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

void Component::sendMessage(const ComponentMessage &message) {
    message.handle(*this);
}

bool Component::isEnabled() const {
    return mIsEnabled;
}

GameObject & Component::getGameObject() const {
    return gameObject;
}

Scene &Component::getCurrentScene() {
    return Dengine::get().getScenesManager().getCurrentScene();
}

std::unique_ptr<Component> Component::clone(GameObject& gameObject) const {
    return std::make_unique<Component>(gameObject);
}
