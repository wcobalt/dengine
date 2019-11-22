#include "GameObject.h"
#include "Dengine.h"
#include "ScenesManager.h"
#include "Scene.h"
#include "Components/Transform/TransformComponent.h"
#include "Initializer.h"
#include "Exceptions/GameObjectException.h"
#include "Filter/Filter.h"
#include "Coreutils/Messages/DirectChildrenChangeMessage.h"
#include "Coreutils/Messages/ParentChangeMessage.h"
#include "Coreutils/Messages/MoveMessage.h"

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

        component->sendMessage(ComponentMessageType::COMPONENT_LOAD, {});
    } else
        throw GameObjectException("Component of such type: " + std::string(typeid(*component).name())
                + " already attached to this game object");
}

void GameObject::detachComponent(std::shared_ptr<Component> component) {
    checkComponentAttachment(component);

    auto it = findComponent(component);

    if (it != components.end()) {
        detachComponent(it);
    } else
        throw GameObjectException("The component is not attached to this game object");
}

void GameObject::detachAllComponents() {
    for (auto it = components.begin(); it != components.end(); it++)
        detachComponent(it);
}

//instantiates game objecton ITS coordinates
void GameObject::instantiate(std::shared_ptr<GameObject> instance) {
    instance->getRoot()->instantiateAsChild(instance);
}

//instantiates the child relate TO PARENT
void GameObject::instantiate(std::shared_ptr<GameObject> instance, float x, float y, float z) {
    instantiate(instance, {x, y, z});
}

//instantiates the child relate TO PARENT
void GameObject::instantiate(std::shared_ptr<GameObject> instance, const vec3f &position) {
    instance->getRoot()->instantiateChild(instance, position);
}

//instantiates game objecton ITS coordinates
void GameObject::instantiateChild(std::shared_ptr<GameObject> instance) {
    instantiateAsChild(instance);
}

//instantiates the child relate TO PARENT
void GameObject::instantiateChild(std::shared_ptr<GameObject> instance, float x, float y, float z) {
    instantiateChild(instance, {x, y, z});
}

//instantiates the child relate TO PARENT
void GameObject::instantiateChild(std::shared_ptr<GameObject> instance, vec3f position) {
    vec3f parentPosition = getComponent<TransformComponent>()->getPosition();

    instance->getComponent<TransformComponent>()->setPosition(position + parentPosition);

    instantiateAsChild(instance);
}

void GameObject::move(std::shared_ptr<GameObject> instance) {
    instance->getRoot()->moveToChildren(instance);
}

void GameObject::moveToChildren(std::shared_ptr<GameObject> instance) {
    std::shared_ptr<GameObject> parent = instance->parent;

    auto iteratorToChildInThatParent = parent->findChild(instance);
    parent->children.erase(iteratorToChildInThatParent);
    parent->sendMessageToComponents(ComponentMessageType::DIRECT_CHILDREN_CHANGE,
            DirectChildrenChangeMessage{DirectChildrenChangeMessage::ChildChangeType::MOVE_FROM, instance});

    addChildWithoutInstantiation(instance, false);

    instance->sendMessage(GameObjectMessageType::MOVE, MoveMessage{parent});
}

void GameObject::destroy(std::shared_ptr<GameObject> instance) {
    bool destroyed = false;

    Filter filter([&destroyed](std::shared_ptr<GameObject> gameObject) {
        gameObject->parent->destroyChild(gameObject);
        destroyed = true;
    },

    [&instance](std::shared_ptr<GameObject> gameObject) -> bool {
        return instance == gameObject;
    }, true);

    filter.run();

    if (!destroyed)
        throw GameObjectException("Cannot destroy the game object because there is no such one in scene tree.");
}

void GameObject::destroyChild(std::shared_ptr<GameObject> instance) {
    auto it = findChild(instance);

    if (it != children.end()) {
        destroyChild(it);
    } else
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

void GameObject::sendMessage(GameObjectMessageType messageType, const Message &message) {
    switch (messageType) {
        case GameObjectMessageType::UPDATE:
            sendMessageToComponents(ComponentMessageType::UPDATE, message);

            break;
        case GameObjectMessageType::INSTANCE_CREATE:
            initialize();

            sendMessageToComponents(ComponentMessageType::INSTANCE_CREATE, message);

            break;
        case GameObjectMessageType::INSTANCE_DESTROY:
            destroyAllChildren();

            sendMessageToComponents(ComponentMessageType::INSTANCE_DESTROY, message);

            detachAllComponents();

            break;
        case GameObjectMessageType::SCENE_UNLOAD:
            sendMessageToComponents(ComponentMessageType::SCENE_UNLOAD, message);

            break;
        case GameObjectMessageType::GAME_END:
            sendMessageToComponents(ComponentMessageType::GAME_END, message);

            break;
        case GameObjectMessageType::MOVE:
            sendMessageToComponents(ComponentMessageType::INSTANCE_MOVE, message);

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
    (*iterator)->sendMessage(ComponentMessageType::COMPONENT_UNLOAD, {});

    components.erase(iterator);
}

GameObject::const_component_iterator GameObject::findComponent(std::shared_ptr<Component> component) const {
    size_t hash = typeid(component).hash_code();

    for (auto it = components.begin(); it != components.end(); it++) {
        if (typeid(*it).hash_code() == hash)
            return it;
    }

    return components.end();
}

void GameObject::initialize() {
    std::shared_ptr<TransformComponent> transform = userDefinedTransform;

    if (!transform)
        transform = std::make_shared<TransformComponent>(shared_from_this());

    attachComponent(transform);

    initializer->initialize(shared_from_this());
}

void GameObject::sendMessageToComponents(ComponentMessageType messageType, const Message &message) {
    for (auto& component : components)
        if (component->isEnabled())
            component->sendMessage(messageType, message);
}

void GameObject::destroyChild(const_iterator iterator) {
    std::shared_ptr<GameObject> child = *iterator;

    (*iterator)->sendMessage(GameObjectMessageType::INSTANCE_DESTROY, {});

    children.erase(iterator);
    sendMessageToComponents(ComponentMessageType::DIRECT_CHILDREN_CHANGE,
            DirectChildrenChangeMessage{DirectChildrenChangeMessage::ChildChangeType::DESTROY, child});
}

std::shared_ptr<GameObject> GameObject::getRoot() const {
    return Dengine::get()->getScenesManager()->getCurrentScene()->getRoot();
}

void GameObject::instantiateAsChild(std::shared_ptr<GameObject> instance) {
    addChildWithoutInstantiation(instance, true);

    instance->sendMessage(GameObjectMessageType::INSTANCE_CREATE, {});
}

GameObject::const_iterator GameObject::findChild(std::shared_ptr<GameObject> instance) const {
    for (auto it = children.begin(); it != children.end(); it++) {
        if (*it == instance) return it;
    }

    return children.end();
}

void GameObject::addChildWithoutInstantiation(std::shared_ptr<GameObject> instance, bool instantiationOrMovingTo) {
    children.emplace_back(instance);
    sendMessageToComponents(ComponentMessageType::DIRECT_CHILDREN_CHANGE,
            DirectChildrenChangeMessage{instantiationOrMovingTo ? DirectChildrenChangeMessage::ChildChangeType::INSTANCE
            : DirectChildrenChangeMessage::ChildChangeType::MOVE_TO, instance});

    std::shared_ptr<GameObject> previousParent = instance->parent;

    instance->parent = shared_from_this();
    instance->sendMessageToComponents(ComponentMessageType::PARENT_CHANGE, ParentChangeMessage{previousParent});
}
