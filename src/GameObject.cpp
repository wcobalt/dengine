#include <optional>

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
#include "Coreutils/Messages/ComponentMessages.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "Filter/CustomFilter.h"
#include "Filter/TraversalMethods/BfsTraversal.h"

using namespace dengine;

GameObject::GameObject() : GameObject(nullptr) {}

GameObject::GameObject(std::unique_ptr<TransformComponent> transform) : userDefinedTransform(std::move(transform)) {}

//STATIC METHODS INSTANTIATE RELATIVE TO ROOT (AND AS ROOT'S CHILD)

//instantiates game object on ITS coordinates
void GameObject::instantiate(const Initializer &initializer) {
    getRoot().instantiateChild(initializer);
}

//instantiates the child relative TO PARENT
void GameObject::instantiate(const Initializer &initializer, float x, float y, float z) {
    instantiate(initializer, {x, y, z});
}

//instantiates the child relative TO PARENT
void GameObject::instantiate(const Initializer &initializer, const vec3f &position) {
    getRoot().instantiateChild(initializer, position);
}

//instantiates game object on ITS coordinates
void GameObject::instantiate(GameObject &instance) {
    getRoot().instantiateChild(instance);
}

//instantiates the child relative TO PARENT
void GameObject::instantiate(GameObject &instance, float x, float y, float z) {
    instantiate(instance, {x, y, z});
}

//instantiates the child relative TO PARENT
void GameObject::instantiate(GameObject &instance, const vec3f &position) {
    getRoot().instantiateChild(instance, position);
}

//NON-STATIC METHODS INSTANTIATE RELATIVE TO PARENT

//instantiates game object on ITS coordinates
void GameObject::instantiateChild(const Initializer &initializer) {
    instantiateAsChild({}, initializer, {});
}

//instantiates the child relative TO PARENT
void GameObject::instantiateChild(const Initializer &initializer, float x, float y, float z) {
    instantiateChild(initializer, {x, y, z});
}

//instantiates the child relative TO PARENT
void GameObject::instantiateChild(const Initializer &initializer, const vec3f &position) {
    instantiateAsChild({}, initializer, position);
}

void GameObject::instantiateNew(const Initializer& initializer, std::optional<vec3f> position) {
    instantiateAsChild(std::make_unique<GameObject>(), initializer, position);
}

//instantiates game object on ITS coordinates
void GameObject::instantiateChild(GameObject &instance) {
    instantiateByCloning(instance, {});
}

//instantiates the child relative TO PARENT
void GameObject::instantiateChild(GameObject &instance, float x, float y, float z) {
    instantiateChild(instance, {x, y, z});
}

//instantiates the child relative TO PARENT
void GameObject::instantiateChild(GameObject &instance, const vec3f &position) {
    instantiateByCloning(instance, position);
}

void GameObject::instantiateByCloning(GameObject& instance, std::optional<vec3f> position) {
    instantiateAsChild(instance.clone(), {}, position);
}

void GameObject::move(GameObject &instance) {
    getRoot().moveToChildren(instance);
}

/*
 * MOVED_FROM
 * MOVED_TO
 * PARENT_CHANGED
 * */

void GameObject::moveToChildren(GameObject &instance) {
    GameObject& instanceParent = instance.getParent();

    //WARNING: WON'T WORK IF THE CHILDREN WILL BE STORED IN NON-CONTIGUOUS CONTAINER

    auto childrenIterator = instanceParent.findChild(instance);
    size_t index = childrenIterator - instanceParent.children.begin();

    //not very graceful (get by index, when there's an iterator (but it's const, so...))
    std::unique_ptr<GameObject> instancePointer = std::move(instanceParent.children[index]);

    //erase
    instanceParent.children.erase(childrenIterator);
    instanceParent.childrenFrontend.erase(instanceParent.childrenFrontend.begin() + index);

    addChildWithoutInstantiation(std::move(instancePointer));

    DirectChildrenChangeMessage moveFromMessage(DirectChildrenChangeMessage::ChildChangeType::MOVE_FROM, instance);
    instanceParent.componentsManager->spreadMessage(moveFromMessage);

    noticeAboutAddingWithoutInstantiation(instance,
                                          DirectChildrenChangeMessage::ChildChangeType::MOVE_TO,
                                          &instanceParent);
}

void GameObject::destroyChild(GameObject &instance) {
    auto it = findChild(instance);

    if (it != children.end()) {
        destroyChild(it);
    } else
        throw GameObjectException("Cannot destroy the child because it is not a child of this game object");
}

void GameObject::destroy() {
    parent->destroyChild(*this);
}

void GameObject::destroyAllChildren() {
    for (auto it = children.begin(); it != children.end(); it++)
        destroyChild(it);
}

GameObject & GameObject::getParent() const {
    return *parent;
}

std::vector<GameObject*> GameObject::getAllChildren() const {
    return childrenFrontend;
}

GameObject::iterator GameObject::begin() {
    return childrenFrontend.begin();
}

GameObject::iterator GameObject::end() {
    return childrenFrontend.end();
}

GameObject::const_iterator GameObject::begin() const {
    return childrenFrontend.begin();
}

GameObject::const_iterator GameObject::end() const {
    return childrenFrontend.end();
}

GameObject::const_iterator GameObject::cbegin() const {
    return childrenFrontend.cbegin();
}

GameObject::const_iterator GameObject::cend() const {
    return childrenFrontend.cend();
}

//reacts only for external events
void GameObject::handleExternalEvent(EventType eventType) {
    switch (eventType) {
        case EventType::UPDATE:
            componentsManager->spreadMessage(UpdateMessage());

            break;
        case EventType::SCENE_UNLOAD:
            componentsManager->spreadMessage(SceneUnloadMessage());

            break;
        case EventType::GAME_END:
            componentsManager->spreadMessage(GameEndMessage());

            break;
    }
}

ComponentsManager & GameObject::getComponentsManager() const {
    return *componentsManager;
}

ID GameObject::getId() const {
    return id;
}

void GameObject::initialize() {
    std::unique_ptr<TransformComponent> transform = std::move(userDefinedTransform);

    if (!userDefinedTransform)
        transform = std::make_unique<TransformComponent>(*this);

    componentsManager->attachComponent(transform);
}

std::unique_ptr<GameObject> GameObject::clone() const {
    return std::unique_ptr<GameObject>();
}

GameObject & GameObject::getRoot() {
    return Dengine::get().getScenesManager().getCurrentScene().getRoot();
}

decltype(GameObject::children)::const_iterator GameObject::findChild(GameObject &instance) const {
    for (auto it = children.begin(); it != children.end(); it++) {
        if (**it == instance) return it;
    }

    return children.end();
}

/*
 * DESTROY ALL CHILDREN
 * DESTRUCTION
 * INSTANCE_DESTROY
 * */

void GameObject::destroyChild(decltype(children)::const_iterator iterator) {
    GameObject& child = **iterator;

    child.destroyAllChildren();

    DirectChildrenChangeMessage destructionMessage(DirectChildrenChangeMessage::ChildChangeType::DESTRUCTION,
                                                   child);

    componentsManager->spreadMessage(destructionMessage);
    child.componentsManager->spreadMessage(InstanceDestroyMessage());

    //not very graceful too
    childrenFrontend.erase(childrenFrontend.begin() + (iterator - children.begin()));
    children.erase(iterator);
}

/*
 * INSTANCE_CREATE
 * INSTANTIATION
 * PARENT_CHANGED
 * */

//instance - non-nullptr
void GameObject::instantiateAsChild(std::unique_ptr<GameObject> instance, const Initializer &initializer,
                                    std::optional<vec3f> position) {
    GameObject& gameObject = *instance;

    if (position) {
        vec3f parentPosition = getTransformComponent().getPosition();

        gameObject.getTransformComponent().setPosition(*position + parentPosition);
    }

    //child is not initialized yet
    addChildWithoutInstantiation(std::move(instance));

    gameObject.id = Dengine::get().getScenesManager().getCurrentScene()->takeNextId();
    gameObject.initialize();
    gameObject.componentsManager->spreadMessage(InstanceCreateMessage());

    noticeAboutAddingWithoutInstantiation(gameObject,
            DirectChildrenChangeMessage::ChildChangeType::INSTANTIATION,
            nullptr);
}

void GameObject::addChildWithoutInstantiation(std::unique_ptr<GameObject> instance) {
    GameObject* instancePointer = instance.get();

    children.emplace_back(std::move(instance));
    childrenFrontend.emplace_back(instancePointer);

    instancePointer->parent = this;
}

void GameObject::noticeAboutAddingWithoutInstantiation(GameObject &instance,
                                                       const DirectChildrenChangeMessage::ChildChangeType &childrenChangeType,
                                                       GameObject *previousParent) {
    DirectChildrenChangeMessage moveToMessage(childrenChangeType, instance);
    componentsManager->spreadMessage(moveToMessage);

    instance.componentsManager->spreadMessage(ParentChangeMessage{*previousParent, *this});
}

bool GameObject::operator==(const GameObject & gameObject) const {
    return id == gameObject.id;
}

bool GameObject::operator!=(const GameObject &gameObject) const {
    return !(*this == gameObject);
}
