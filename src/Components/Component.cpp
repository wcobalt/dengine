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

void Component::onUpdate() {}

void Component::onInstanceDestroy() {}

void Component::onSceneUnload() {}

void Component::onGameEnd() {}

void Component::setEnabled(bool isEnabled) {
    mIsEnabled = isEnabled;
}

void Component::sendMessage(ComponentMessage message) {
    switch (message) {
        case ComponentMessage::INSTANCE_CREATE:
            onInstanceCreate();

            break;
        case ComponentMessage::INSTANCE_DESTROY:
            onInstanceDestroy();

            break;
        case ComponentMessage::COMPONENT_LOAD:
            onComponentLoad();

            break;
        case ComponentMessage::COMPONENT_UNLOAD:
            onComponentUnload();

            break;
        case ComponentMessage::UPDATE:
            onUpdate();

            break;
        case ComponentMessage::SCENE_UNLOAD:
            onSceneUnload();

            break;
        case ComponentMessage::GAME_END:
            onGameEnd();
            
            break;
    }
}

bool Component::isEnabled() const {
    return mIsEnabled;
}

std::shared_ptr<GameObject> Component::getGameObject() const {
    return gameObject;
}
