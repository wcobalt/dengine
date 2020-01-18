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
#include "ComponentsManager.h"

using namespace dengine;

GameObject::GameObject() : GameObject(nullptr, nullptr) {}

GameObject::GameObject(std::shared_ptr<Initializer> initializer) : GameObject(initializer, nullptr) {}

GameObject::GameObject(std::shared_ptr<TransformComponent> transform) : GameObject(nullptr, transform) {}

GameObject::GameObject(std::shared_ptr<Initializer> initializer, std::shared_ptr<TransformComponent> transform)
        : initializer(initializer), userDefinedTransform(transform) {
    id = Dengine::get()->getScenesManager()->getCurrentScene()->takeNextId();
    componentsManager = std::make_shared<ComponentsManager>(shared_from_this());
}

//instantiates game object on ITS coordinates
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
    vec3f parentPosition = componentsManager->getComponent<TransformComponent>()->getPosition();

    instance->getComponentsManager()->getComponent<TransformComponent>()->setPosition(position + parentPosition);

    instantiateAsChild(instance);
}

void GameObject::move(std::shared_ptr<GameObject> instance) {
    instance->getRoot()->moveToChildren(instance);
}

/*
 * MOVED_FROM
 * MOVED_TO
 * PARENT_CHANGED
 * */

void GameObject::moveToChildren(std::shared_ptr<GameObject> instance) {
    std::shared_ptr<GameObject> parent = instance->getParent();

    parent->children.erase(parent->findChild(instance));
    addChildWithoutInstantiation(instance);

    DirectChildrenChangeMessage moveFromMessage(DirectChildrenChangeMessage::ChildChangeType::MOVE_FROM, instance);
    parent->componentsManager->sendMessage(ComponentsManager::MessageType::DIRECT_CHILDREN_CHANGE, moveFromMessage);

    noticeAboutAddingWithoutInstantiation(instance,
            DirectChildrenChangeMessage::ChildChangeType::MOVE_TO,
            parent);
}

void GameObject::destroy(std::shared_ptr<GameObject> instance) {
    bool destroyed = false;

    Filter filter([&destroyed](std::shared_ptr<GameObject> gameObject) {
        gameObject->destroy();
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

void GameObject::destroy() {
    parent->destroyChild(shared_from_this());
}

void GameObject::destroyAllChildren() {
    for (auto it = children.begin(); it != children.end(); it++)
        destroyChild(it);
}

std::shared_ptr<GameObject> GameObject::getParent() const {
    return parent;
}

std::vector<std::shared_ptr<GameObject>> GameObject::getAllChildren() const {
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

//reacts only for extern events
void GameObject::sendMessage(MessageType messageType) {
    switch (messageType) {
        case MessageType::UPDATE:
            componentsManager->sendMessage(ComponentsManager::MessageType::UPDATE, {});

            break;
        case MessageType::SCENE_UNLOAD:
            componentsManager->sendMessage(ComponentsManager::MessageType::SCENE_UNLOAD, {});

            break;
        case MessageType::GAME_END:
            componentsManager->sendMessage(ComponentsManager::MessageType::GAME_END, {});

            break;
    }
}

std::shared_ptr<ComponentsManager> GameObject::getComponentsManager() const {
    return componentsManager;
}

ID GameObject::getId() const {
    return id;
}

void GameObject::initialize() {
    std::shared_ptr<TransformComponent> transform = userDefinedTransform;

    if (!transform)
        transform = std::make_shared<TransformComponent>(shared_from_this());

    componentsManager->attachComponent(transform);

    initializer->initialize(shared_from_this());
}

std::shared_ptr<GameObject> GameObject::getRoot() {
    return Dengine::get()->getScenesManager()->getCurrentScene()->getRoot();
}

GameObject::const_iterator GameObject::findChild(std::shared_ptr<GameObject> instance) const {
    for (auto it = children.begin(); it != children.end(); it++) {
        if (*it == instance) return it;
    }

    return children.end();
}

/*
 * DESTROY ALL CHILDREN
 * DESTRUCTION
 * INSTANCE_DESTROY
 * */

void GameObject::destroyChild(const_iterator iterator) {
    std::shared_ptr<GameObject> child = *iterator;

    child->destroyAllChildren();

    DirectChildrenChangeMessage destructionMessage(DirectChildrenChangeMessage::ChildChangeType::DESTRUCTION,
                                                   child);

    componentsManager->sendMessage(ComponentsManager::MessageType::DIRECT_CHILDREN_CHANGE, destructionMessage);
    child->componentsManager->sendMessage(ComponentsManager::MessageType::INSTANCE_DESTROY, {});

    children.erase(iterator);
}

/*
 * INSTANCE_CREATE
 * INSTANTIATION
 * PARENT_CHANGED
 * */

void GameObject::instantiateAsChild(std::shared_ptr<GameObject> instance) {
    std::shared_ptr<GameObject> clone = instance->clone();

    //child is not initialized yet
    addChildWithoutInstantiation(clone);

    clone->initialize();

    clone->componentsManager->sendMessage(ComponentsManager::MessageType::INSTANCE_CREATE, {});

    noticeAboutAddingWithoutInstantiation(clone,
            DirectChildrenChangeMessage::ChildChangeType::INSTANTIATION,
            nullptr);
}

void GameObject::addChildWithoutInstantiation(std::shared_ptr<GameObject> instance) {
    children.emplace_back(instance);
    instance->parent = shared_from_this();
}

void GameObject::noticeAboutAddingWithoutInstantiation(std::shared_ptr<GameObject> instance,
                                                       const DirectChildrenChangeMessage::ChildChangeType &childrenChangeType,
                                                       std::shared_ptr<GameObject> previousParent) {
    DirectChildrenChangeMessage moveToMessage(childrenChangeType, instance);
    componentsManager->sendMessage(ComponentsManager::MessageType::DIRECT_CHILDREN_CHANGE, moveToMessage);

    instance->componentsManager->sendMessage(
            ComponentsManager::MessageType::PARENT_CHANGE,
            ParentChangeMessage{previousParent, shared_from_this()});
}