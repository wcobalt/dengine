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

        component->sendMessage(Component::MessageType::COMPONENT_LOAD, {});
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

void ComponentsManager::sendMessage(MessageType messageType, const ComponentMessage &message) {
    switch (messageType) {
        case MessageType::UPDATE:
            sendMessageToComponents(Component::MessageType::UPDATE, message);

            break;
        case MessageType::INSTANCE_CREATE:
            sendMessageToComponents(Component::MessageType::INSTANCE_CREATE, message);

            break;
        case MessageType::INSTANCE_DESTROY:
            sendMessageToComponents(Component::MessageType::INSTANCE_DESTROY, message);

            detachAllComponents();

            break;
        case MessageType::SCENE_UNLOAD:
            sendMessageToComponents(Component::MessageType::SCENE_UNLOAD, message);

            break;
        case MessageType::GAME_END:
            sendMessageToComponents(Component::MessageType::GAME_END, message);

            break;
        case MessageType::DIRECT_CHILDREN_CHANGE:
            sendMessageToComponents(Component::MessageType::DIRECT_CHILDREN_CHANGE, message);

            break;
        case MessageType::PARENT_CHANGE:
            sendMessageToComponents(Component::MessageType::PARENT_CHANGE, message);

            break;
    }
}

void ComponentsManager::detachComponent(ComponentsManager::const_component_iterator iterator) {
    (*iterator)->sendMessage(Component::MessageType::COMPONENT_UNLOAD, {});

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

void ComponentsManager::sendMessageToComponents(Component::MessageType messageType, const ComponentMessage &message) {
    for (auto& component : components)
        if (component->isEnabled())
            component->sendMessage(messageType, message);
}
