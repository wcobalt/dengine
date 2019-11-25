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
    vec3f parentPosition = componentsManager->getComponent<TransformComponent>()->getPosition();

    instance->getComponentsManager()->getComponent<TransformComponent>()->setPosition(position + parentPosition);

    instantiateAsChild(instance);
}

void GameObject::move(std::shared_ptr<GameObject> instance) {
    instance->getRoot()->moveToChildren(instance);
}

void GameObject::moveToChildren(std::shared_ptr<GameObject> instance) {
    std::shared_ptr<GameObject> parent = instance->parent;

    auto iteratorToChildInThatParent = parent->findChild(instance);
    parent->children.erase(iteratorToChildInThatParent);
    parent->sendMessage(GameObjectMessageType::DIRECT_CHILDREN_CHANGE,
            DirectChildrenChangeMessage(DirectChildrenChangeMessage::ChildChangeType::MOVE_FROM, instance));

    addChildWithoutInstantiation(instance, false);

    instance->sendMessage(GameObjectMessageType::INSTANCE_MOVE, MoveMessage(parent));
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

/*
 * So, sendMessage(semantic synonym - notify) is a method which responses on a message in proper way.
 * Actually, this method is called when on higher level, something will happen or was happened with the object.
 * Actions which necessary must be executed on higher level are executed there, but actions which COULD be executed as on higher
 * as on lower one, are executed on lower. So, developer of lower level sendMessage() logic, cannot rely on some actions
 * which could be executed somewhere on higher level. For instance:
 *
 * we have to destroy some GO (GameObject), since each GO is someone's child we must delete it from parent (parent, at this case
 * - is higher level, child is lower one). But before that we need to make child GO deleted itself. So, we notify it,
 * that it will be destroyed soon, and it cannot rely that IT's OWN children will be destroyed by someone, so it does it in it's own.
 * Like this, it cannot rely that IT's OWN components will be detached by someone, so it does itself.
 *
 * TL;DR: lower level must do work about itself, higher one about itself. Lower one cannot rely on higher one. sendMessage
 * is notification about something that was happened or will happen. It can be just notification (delegation of message to lower
 * levels) but can contain some logic as well.
 * */
void GameObject::sendMessage(GameObjectMessageType messageType, const Message &message) {
    switch (messageType) {
        case GameObjectMessageType::UPDATE:
            componentsManager->sendMessage(ComponentsManagerMessageType::UPDATE, message);

            break;
        case GameObjectMessageType::INSTANCE_CREATE_PRE:
            initialize();

            break;
        case GameObjectMessageType::INSTANCE_CREATE_POST:
            componentsManager->sendMessage(ComponentsManagerMessageType::INSTANCE_CREATE, message);

            break;
        case GameObjectMessageType::INSTANCE_DESTROY:
            destroyAllChildren();

            componentsManager->sendMessage(ComponentsManagerMessageType::INSTANCE_DESTROY, message);

            break;
        case GameObjectMessageType::SCENE_UNLOAD:
            componentsManager->sendMessage(ComponentsManagerMessageType::SCENE_UNLOAD, message);

            break;
        case GameObjectMessageType::GAME_END:
            componentsManager->sendMessage(ComponentsManagerMessageType::GAME_END, message);

            break;
        case GameObjectMessageType::INSTANCE_MOVE:
            componentsManager->sendMessage(ComponentsManagerMessageType::INSTANCE_MOVE, message);

            break;
        case GameObjectMessageType::DIRECT_CHILDREN_CHANGE:
            componentsManager->sendMessage(ComponentsManagerMessageType::DIRECT_CHILDREN_CHANGE, message);

            break;
        case GameObjectMessageType::PARENT_CHANGE:
            componentsManager->sendMessage(ComponentsManagerMessageType::PARENT_CHANGE, message);

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

void GameObject::destroyChild(const_iterator iterator) {
    std::shared_ptr<GameObject> child = *iterator;

    child->sendMessage(GameObjectMessageType::INSTANCE_DESTROY, {});

    children.erase(iterator);
    sendMessage(GameObjectMessageType::DIRECT_CHILDREN_CHANGE,
            DirectChildrenChangeMessage(DirectChildrenChangeMessage::ChildChangeType::DESTROY, child));
}

void GameObject::instantiateAsChild(std::shared_ptr<GameObject> instance) {
    std::shared_ptr<GameObject> clone = instance->clone();

    clone->sendMessage(GameObjectMessageType::INSTANCE_CREATE_PRE, {});

    addChildWithoutInstantiation(clone, true);

    clone->sendMessage(GameObjectMessageType::INSTANCE_CREATE_POST, {});
}

void GameObject::addChildWithoutInstantiation(std::shared_ptr<GameObject> instance, bool instantiationOrMovingTo) {
    children.emplace_back(instance);

    DirectChildrenChangeMessage message(instantiationOrMovingTo ? DirectChildrenChangeMessage::ChildChangeType::INSTANTIATION
                                                                : DirectChildrenChangeMessage::ChildChangeType::MOVE_TO, instance);

    sendMessage(GameObjectMessageType::DIRECT_CHILDREN_CHANGE, message);

    std::shared_ptr<GameObject> previousParent = instance->parent;

    instance->parent = shared_from_this();
    instance->sendMessage(GameObjectMessageType::PARENT_CHANGE,
            ParentChangeMessage(previousParent));
}
