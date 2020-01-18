//
// Created by wcobalt on 3/30/19.
//
#include <memory>

#include "Component.h"
#include "../GameObject.h"
#include "../Exceptions/ComponentException.h"
#include "../Exceptions/IllegalArgumentException.h"
#include "../Coreutils/Messages/ParentChangeMessage.h"
#include "../Coreutils/Messages/DirectChildrenChangeMessage.h"

using namespace dengine;

Component::Component(std::shared_ptr<GameObject> gameObject) {
    if (gameObject == nullptr) throw IllegalArgumentException("Game object cannot be null");

    this->gameObject = gameObject;
}

void Component::onInstanceCreate(const ComponentMessage &message) {}

void Component::onComponentLoad(const ComponentMessage &message) {}

void Component::onComponentUnload(const ComponentMessage &message) {}

void Component::onUpdate(const ComponentMessage &message) {}

void Component::onInstanceDestroy(const ComponentMessage &message) {}

void Component::onSceneUnload(const ComponentMessage &message) {}

void Component::onGameEnd(const ComponentMessage &message) {}

void Component::onDirectChildrenChange(const DirectChildrenChangeMessage &message) {}

void Component::onParentChange(const ParentChangeMessage &message) {}

void Component::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

void Component::sendMessage(MessageType messageType, const ComponentMessage &message) {
    switch (messageType) {
        case MessageType::INSTANCE_CREATE:
            onInstanceCreate(message);

            break;
        case MessageType::INSTANCE_DESTROY:
            onInstanceDestroy(message);

            break;
        case MessageType::COMPONENT_LOAD:
            onComponentLoad(message);

            break;
        case MessageType::COMPONENT_UNLOAD:
            onComponentUnload(message);

            break;
        case MessageType::UPDATE:
            onUpdate(message);

            break;
        case MessageType::SCENE_UNLOAD:
            onSceneUnload(message);

            break;
        case MessageType::GAME_END:
            onGameEnd(message);

            break;
        case MessageType::PARENT_CHANGE:
            onParentChange(dynamic_cast<const ParentChangeMessage&>(message)); //i'm sure it isn't good. may be add some checks?

            break;
        case MessageType::DIRECT_CHILDREN_CHANGE:
            onDirectChildrenChange(dynamic_cast<const DirectChildrenChangeMessage&>(message));

            break;
    }
}

bool Component::isEnabled() const {
    return mIsEnabled;
}

std::shared_ptr<GameObject> Component::getGameObject() const {
    return gameObject;
}
