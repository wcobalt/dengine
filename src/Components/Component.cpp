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
#include "../Coreutils/Messages/MoveMessage.h"

using namespace dengine;

Component::Component(std::shared_ptr<GameObject> gameObject) {
    if (gameObject == nullptr) throw IllegalArgumentException("Game object cannot be null");

    this->gameObject = gameObject;
}

void Component::onInstanceCreate(const Message &message) {}

void Component::onComponentLoad(const Message &message) {}

void Component::onComponentUnload(const Message &message) {}

void Component::onUpdate(const Message &message) {}

void Component::onInstanceDestroy(const Message &message) {}

void Component::onSceneUnload(const Message &message) {}

void Component::onGameEnd(const Message &message) {}

void Component::onDirectChildrenChange(const DirectChildrenChangeMessage &message) {}

void Component::onParentChange(const ParentChangeMessage &message) {}

void Component::onMove(const MoveMessage &message) {}

void Component::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

void Component::sendMessage(ComponentMessageType messageType, const Message &message) {
    switch (messageType) {
        case ComponentMessageType::INSTANCE_CREATE:
            onInstanceCreate(message);

            break;
        case ComponentMessageType::INSTANCE_DESTROY:
            onInstanceDestroy(message);

            break;
        case ComponentMessageType::COMPONENT_LOAD:
            onComponentLoad(message);

            break;
        case ComponentMessageType::COMPONENT_UNLOAD:
            onComponentUnload(message);

            break;
        case ComponentMessageType::UPDATE:
            onUpdate(message);

            break;
        case ComponentMessageType::SCENE_UNLOAD:
            onSceneUnload(message);

            break;
        case ComponentMessageType::GAME_END:
            onGameEnd(message);

            break;
        case ComponentMessageType::PARENT_CHANGE:
            onParentChange(dynamic_cast<const ParentChangeMessage&>(message)); //i'm sure it's not good. may be add some checks?

            break;
        case ComponentMessageType::DIRECT_CHILDREN_CHANGE:
            onDirectChildrenChange(dynamic_cast<const DirectChildrenChangeMessage&>(message));

            break;
        case ComponentMessageType::INSTANCE_MOVE:
            onMove(dynamic_cast<const MoveMessage&>(message));

            break;
    }
}

bool Component::isEnabled() const {
    return mIsEnabled;
}

std::shared_ptr<GameObject> Component::getGameObject() const {
    return gameObject;
}
