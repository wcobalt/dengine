#include "GameObject.h"
#include "Dengine.h"
#include "ScenesManager.h"
#include "Scene.h"
#include "Components/TransformComponent.h"
#include "Initializer.h"
#include "Exceptions/GameObjectException.h"
#include "Filter/Filter.h"

using namespace dengine;

GameObject::GameObject() : GameObject(nullptr, nullptr) {}

GameObject::GameObject(std::shared_ptr<Initializer> initializer) : GameObject(initializer, nullptr) {}

GameObject::GameObject(std::shared_ptr<TransformComponent> transform) : GameObject(nullptr, transform) {}

GameObject::GameObject(std::shared_ptr<Initializer> initializer, std::shared_ptr<TransformComponent> transform)
        : initializer(initializer), userDefinedTransform(transform) {
    id = Dengine::get()->getScenesManager()->getCurrentScene()->takeNextId();
}

void GameObject::attachComponent(std::shared_ptr<Component> component) {
    checkComponentAttachment(component);

    auto it = findComponent(component);

    if (it == components.end()) {
        components.emplace_back(component);

        component->sendMessage(ComponentMessage::COMPONENT_LOAD);
    } else throw GameObjectException("Component of such type: " + std::string(typeid(*component).name())
                + " already attached to this game object");
}

void GameObject::detachComponent(std::shared_ptr<Component> component) {
    checkComponentAttachment(component);

    auto it = findComponent(component);

    if (it != components.end()) {
        detachComponent(it);
    } else throw GameObjectException("The component is not attached to this game object");
}

void GameObject::instantiate(std::shared_ptr<GameObject> instance) {
    std::shared_ptr<GameObject> root = Dengine::get()->getScenesManager()->getCurrentScene()->getRoot();

    root->instantiateChild(instance);
}

void GameObject::instantiateChild(std::shared_ptr<GameObject> instance) {
    children.emplace_back(instance);
    instance->parent = shared_from_this();

    instance->sendMessage(GameObjectMessage::INSTANCE_CREATE);
}

void GameObject::destroy(std::shared_ptr<GameObject> instance) {
    bool destroyed = false;

    Filter filter([&destroyed](std::shared_ptr<GameObject> gameObject) {
        gameObject->parent->destroyChild(gameObject);
        destroyed = true;

        return true;
    },

    [&instance](std::shared_ptr<GameObject> gameObject) -> bool {
        return instance == gameObject;
    });

    if (!destroyed)
        throw GameObjectException("Cannot destroy the game object because there is no such one in scene tree.");
}

void GameObject::destroyChild(std::shared_ptr<GameObject> instance) {
    for (auto it = children.begin(); it != children.end(); it++) {
        if (instance == *it) {
            destroyChild(it);

            return;
        }
    }

    throw GameObjectException("Cannot destroy the child because it is not a child of this game object");
}

void GameObject::destroyAllChildren() {
    for (auto it = children.begin(); it != children.end(); it++)
        destroyChild(it);
}

std::shared_ptr<GameObject> GameObject::getParent() const {
    return parent;
}

std::vector<std::shared_ptr<GameObject>> GameObject::getChildren() const {
    return children;
}

GameObject::iterator GameObject::begin() {
    return children.begin();
}

GameObject::iterator GameObject::end() {
    return children.end();
}

GameObject::const_iterator GameObject::begin() const {
    return children.begin();
}

GameObject::const_iterator GameObject::end() const {
    return children.end();
}

GameObject::const_iterator GameObject::cbegin() const {
    return children.cbegin();
}

GameObject::const_iterator GameObject::cend() const {
    return children.cend();
}

std::vector<std::shared_ptr<Component>> GameObject::getAllComponents() const {
    return components;
}

void GameObject::sendMessage(GameObjectMessage message) {
    switch (message) {
        case GameObjectMessage::UPDATE:
            sendMessageToComponents(ComponentMessage::UPDATE);

            break;
        case GameObjectMessage::INSTANCE_CREATE:
            initialize();

            sendMessageToComponents(ComponentMessage::INSTANCE_CREATE);

            break;
        case GameObjectMessage::INSTANCE_DESTROY:
            sendMessageToComponents(ComponentMessage::INSTANCE_DESTROY);

            destroyAllChildren();

            break;
        case GameObjectMessage::SCENE_UNLOAD:
            sendMessageToComponents(ComponentMessage::SCENE_UNLOAD);

            break;
        case GameObjectMessage::GAME_END:
            sendMessageToComponents(ComponentMessage::GAME_END);

            break;
    }
}

ID GameObject::getId() const {
    return id;
}

void GameObject::checkComponentAttachment(std::shared_ptr<Component> component) {
    if (component->getGameObject() != shared_from_this())
        throw GameObjectException("Game object which components bound to and this game object are different.");
}

void GameObject::detachComponent(GameObject::const_component_iterator iterator) {
    (*iterator)->sendMessage(ComponentMessage::COMPONENT_UNLOAD);

    components.erase(iterator);
}

GameObject::const_component_iterator GameObject::findComponent(std::shared_ptr<Component> component) const {
    size_t hash = typeid(component).hash_code();

    for (auto it = components.begin(); it != components.end(); it++) {
        if (typeid(*it).hash_code() == hash)
            return it;
    }
}

void GameObject::initialize() {
    std::shared_ptr<TransformComponent> transform = userDefinedTransform;

    if (!transform)
        transform = std::make_shared<TransformComponent>(shared_from_this());

    attachComponent(transform);

    initializer->initialize(shared_from_this());
}

void GameObject::sendMessageToComponents(ComponentMessage message) {
    for (auto& component : components)
        component->sendMessage(message);
}

void GameObject::destroyChild(const_iterator iterator) {
    (*iterator)->sendMessage(GameObjectMessage::INSTANCE_DESTROY);

    children.erase(iterator);
}
