//
// Created by wcobalt on 11/25/19.
//

#include "ComponentsManager.h"
#include "Components/Component.h"
#include "GameObject.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "Coreutils/Messages/ComponentMessages.h"
#include "Dengine.h"
#include "Components/Transform/TransformComponent.h"

using namespace dengine;

ComponentsManager::ComponentsManager(GameObject &gameObject) : gameObject(gameObject) {}

void ComponentsManager::attachComponent(std::unique_ptr<Component> component) {
    checkComponentAttachment(*component);

    auto it = findComponent(*component);

    if (it == components.end()) {
        Component& componentReference = *component;

        components.emplace_back(std::move(component));
        componentsFrontend.emplace_back(&componentReference);

        if (transformComponent == nullptr &&
            typeid(componentReference).hash_code() == typeid(TransformComponent).hash_code()) {

            transformComponent = dynamic_cast<TransformComponent *>(&componentReference);
        }

        componentReference.sendMessage(ComponentLoadMessage());
    } else
        throw ComponentException("Component of such type: " + std::string(typeid(*component).name())
                                 + " already attached to this game object");
}

void ComponentsManager::detachComponent(const Component &component) {
    if (&component != transformComponent) {
        checkComponentAttachment(component);

        auto it = findComponent(component);

        if (it != components.end()) {
            detachComponent(it);
        } else
            throw ComponentException("The component is not attached to this game object");
    } else
        throw ComponentException("It's impossible to detach TransformComponent");
}

void ComponentsManager::detachAllComponents() {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (&**it != transformComponent)
            detachComponent(it);
    }
}

void ComponentsManager::spreadMessage(const ComponentMessage &message) {
    if (gameObject.getComponentsManager().getTransformComponent().isActive()) {
        for (auto &component : components)
            if (component->isEnabled())
                component->sendMessage(message);
    }
}

void ComponentsManager::detachComponent(decltype(components)::const_iterator iterator) {
    (*iterator)->sendMessage(ComponentUnloadMessage());

    components.erase(iterator);
    componentsFrontend.erase(componentsFrontend.begin() + (iterator - components.begin()));
}

void ComponentsManager::checkComponentAttachment(const Component &component) {
    if (!isComponentAttached(component))
        throw ComponentException("Game object that component is bound to and this game object are different.");
}

decltype(ComponentsManager::components)::const_iterator ComponentsManager::findComponent(const Component &component) const {
    size_t hash = typeid(component).hash_code();

    for (auto it = components.begin(); it != components.end(); ++it) {
        if (typeid(*it).hash_code() == hash)
            return it;
    }

    return components.end();
}

ComponentsManager::iterator ComponentsManager::begin() {
    return componentsFrontend.begin();
}

ComponentsManager::iterator ComponentsManager::end() {
    return componentsFrontend.end();
}

ComponentsManager::const_iterator ComponentsManager::begin() const {
    return componentsFrontend.cbegin();
}

ComponentsManager::const_iterator ComponentsManager::end() const {
    return componentsFrontend.cend();
}

ComponentsManager::const_iterator ComponentsManager::cbegin() const {
    return componentsFrontend.cbegin();
}

ComponentsManager::const_iterator ComponentsManager::cend() const {
    return componentsFrontend.cend();
}

std::unique_ptr<ComponentsManager> ComponentsManager::clone(GameObject& gameObject) const {
    std::unique_ptr<ComponentsManager> clone = std::make_unique<ComponentsManager>(gameObject);

    for (auto child : *this) {
        clone->attachComponent(child->clone(gameObject));
    }

    return clone;
}

TransformComponent &ComponentsManager::getTransformComponent() const {
    if (transformComponent != nullptr) {
        return *transformComponent;
    } else
        throw ComponentException("Unable to return TransformComponent since it was not attached yet");
}

bool ComponentsManager::isComponentAttached(const Component &component) const {
    return component.getGameObject() == gameObject;
}
