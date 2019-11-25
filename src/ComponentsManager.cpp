//
// Created by wcobalt on 11/25/19.
//

#include "ComponentsManager.h"
#include "Components/Component.h"

using namespace dengine;

ComponentsManager::ComponentsManager(std::shared_ptr<GameObject> gameObject) : gameObject(gameObject) {}

void ComponentsManager::attachComponent(std::shared_ptr<Component> component) {
    checkComponentAttachment(component);

    auto it = findComponent(component);

    if (it == components.end()) {
        components.emplace_back(component);

        component->sendMessage(ComponentMessageType::COMPONENT_LOAD, {});
    } else
        throw ComponentException("Component of such type: " + std::string(typeid(*component).name())
                                  + " already attached to this game object");
}

void ComponentsManager::detachComponent(std::shared_ptr<Component> component) {
    checkComponentAttachment(component);

    auto it = findComponent(component);

    if (it != components.end()) {
        detachComponent(it);
    } else
        throw ComponentException("The component is not attached to this game object");
}

void ComponentsManager::detachAllComponents() {
    for (auto it = components.begin(); it != components.end(); it++)
        detachComponent(it);
}

std::vector<std::shared_ptr<Component>> ComponentsManager::getAllComponents() const {
    return components;
}

void ComponentsManager::sendMessage(ComponentsManagerMessageType messageType, const Message &message) {
    switch (messageType) {
        case ComponentsManagerMessageType::UPDATE:
            sendMessageToComponents(ComponentMessageType::UPDATE, message);

            break;
        case ComponentsManagerMessageType::INSTANCE_CREATE:
            sendMessageToComponents(ComponentMessageType::INSTANCE_CREATE, message);

            break;
        case ComponentsManagerMessageType::INSTANCE_DESTROY:
            sendMessageToComponents(ComponentMessageType::INSTANCE_DESTROY, message);

            detachAllComponents();

            break;
        case ComponentsManagerMessageType::SCENE_UNLOAD:
            sendMessageToComponents(ComponentMessageType::SCENE_UNLOAD, message);

            break;
        case ComponentsManagerMessageType::GAME_END:
            sendMessageToComponents(ComponentMessageType::GAME_END, message);

            break;
        case ComponentsManagerMessageType::INSTANCE_MOVE:
            sendMessageToComponents(ComponentMessageType::INSTANCE_MOVE, message);

            break;
        case ComponentsManagerMessageType::DIRECT_CHILDREN_CHANGE:
            sendMessageToComponents(ComponentMessageType::DIRECT_CHILDREN_CHANGE, message);

            break;
        case ComponentsManagerMessageType::PARENT_CHANGE:
            sendMessageToComponents(ComponentMessageType::PARENT_CHANGE, message);

            break;
    }
}

void ComponentsManager::detachComponent(ComponentsManager::const_component_iterator iterator) {
    (*iterator)->sendMessage(ComponentMessageType::COMPONENT_UNLOAD, {});

    components.erase(iterator);
}

void ComponentsManager::checkComponentAttachment(std::shared_ptr<Component> component) {
    if (component->getGameObject() != gameObject)
        throw ComponentException("Game object component is bound to and this game object are different.");
}

ComponentsManager::const_component_iterator ComponentsManager::findComponent(std::shared_ptr<Component> component) const {
    size_t hash = typeid(component).hash_code();

    for (auto it = components.begin(); it != components.end(); it++) {
        if (typeid(*it).hash_code() == hash)
            return it;
    }

    return components.end();
}

void ComponentsManager::sendMessageToComponents(ComponentMessageType messageType, const Message &message) {
    for (auto& component : components)
        if (component->isEnabled())
            component->sendMessage(messageType, message);
}
