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

using namespace dengine;

//STATIC METHODS INSTANTIATE RELATIVE TO ROOT (AND AS ROOT'S CHILD)

//instantiates game object on ITS coordinates
GameObject & GameObject::instantiate(const Initializer &initializer) {
    return getRoot().instantiateChild(initializer);
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiate(const Initializer &initializer, float x, float y, float z) {
    return instantiate(initializer, {x, y, z});
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiate(const Initializer &initializer, const vec3f &position) {
    return getRoot().instantiateChild(initializer, position);
}

//instantiates game object on ITS coordinates
GameObject & GameObject::instantiate(GameObject &instance) {
    return getRoot().instantiateChild(instance);
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiate(GameObject &instance, float x, float y, float z) {
    return instantiate(instance, {x, y, z});
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiate(GameObject &instance, const vec3f &position) {
    return getRoot().instantiateChild(instance, position);
}

//NON-STATIC METHODS INSTANTIATE RELATIVE TO PARENT

//instantiates game object on ITS coordinates
GameObject & GameObject::instantiateChild(const Initializer &initializer) {
    return instantiateNew(initializer, {});
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiateChild(const Initializer &initializer, float x, float y, float z) {
    return instantiateChild(initializer, {x, y, z});
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiateChild(const Initializer &initializer, const vec3f &position) {
    return instantiateNew(initializer, position);
}

GameObject & GameObject::instantiateNew(const Initializer& initializer, std::optional<vec3f> position) {
    return instantiateAsChild(std::make_unique<GameObject>(), initializer, position, false);
}

//instantiates game object on ITS coordinates
GameObject & GameObject::instantiateChild(GameObject &instance) {
    return instantiateByCloning(instance, {});
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiateChild(GameObject &instance, float x, float y, float z) {
    return instantiateChild(instance, {x, y, z});
}

//instantiates the child relative TO PARENT
GameObject & GameObject::instantiateChild(GameObject &instance, const vec3f &position) {
    return instantiateByCloning(instance, position);
}

GameObject & GameObject::instantiateByCloning(GameObject& instance, std::optional<vec3f> position) {
    return instantiateAsChild(instance.clone(), {}, position, true);
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

    notifyAboutAdditionWithoutInstantiation(instance,
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

void GameObject::initialize(bool doAddTransform) {
    if (doAddTransform) {
        std::unique_ptr<TransformComponent> transform = std::make_unique<TransformComponent>(*this);

        componentsManager->attachComponent(std::move(transform));
    }
}

//clones children and components manager
std::unique_ptr<GameObject> GameObject::clone() const {
    std::unique_ptr<GameObject> clone = std::make_unique<GameObject>();

    for (auto child : *this) {
        clone->addChildWithoutInstantiation(child->clone());
    }

    clone->componentsManager = componentsManager->clone(*clone);

    return clone;
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

//instance - non-nullptr (all children have right parent), haveTransform: if inst. trough Initializer - false, trough clone() - true
GameObject & GameObject::instantiateAsChild(std::unique_ptr<GameObject> instance, const Initializer &initializer,
                                            std::optional<vec3f> position, bool haveTransforms) {
    GameObject& gameObject = *instance;

    //child is not initialized yet (just warning)
    addChildWithoutInstantiation(std::move(instance));

    gameObject.propagateInstantiation(initializer, haveTransforms);

    if (position) {
        vec3f parentPosition = getParent().getTransformComponent().getPosition();

        getTransformComponent().setPosition(*position + parentPosition);
    }

    initializer.initialize(*this);

    gameObject.propagateInstantiationNotification();

    //@todo propagate notification to children

    return gameObject;
}

/*
 * There's a rule: before GO/Component/etc is notified about something it HAS TO be in valid state.
 * So: first of all GO and all its children are instantiated, then notification propagation is
 * launched.
 * */
void
GameObject::propagateInstantiation(const Initializer &initializer, bool haveTransforms) {
    //children are instantiated first because when execution comes to initializer, GO must be in valid state

    for (auto child : *this) {
        child->propagateInstantiation(initializer, haveTransforms);
    }

    id = Dengine::get().getScenesManager().getCurrentScene().takeNextId();
    initialize(!haveTransforms);//adds transform only if there's no one yet
}

/*
 * Is used to notify all children recursively and then the GO itself about
 * their first come to scene (when they are instantiated).
 * */
void GameObject::propagateInstantiationNotification() {
    //children first because parent may depends on them. (Yes children may depend on parent as well but
    //for good children event shouldn't know about parent)
    for (auto child : *this) {
        child->propagateInstantiationNotification();
    }

    componentsManager->spreadMessage(InstanceCreateMessage());

    getParent().notifyAboutAdditionWithoutInstantiation(*this,
                                                        DirectChildrenChangeMessage::ChildChangeType::INSTANTIATION,
                                                        nullptr);
}

void GameObject::addChildWithoutInstantiation(std::unique_ptr<GameObject> instance) {
    GameObject* instancePointer = instance.get();

    children.emplace_back(std::move(instance));
    childrenFrontend.emplace_back(instancePointer);

    instancePointer->parent = this;
}

void GameObject::notifyAboutAdditionWithoutInstantiation(GameObject &instance,
                                                         const DirectChildrenChangeMessage::ChildChangeType &childrenChangeType,
                                                         GameObject *previousParent) {
    DirectChildrenChangeMessage moveToMessage(childrenChangeType, instance);
    componentsManager->spreadMessage(moveToMessage);

    instance.componentsManager->spreadMessage(ParentChangeMessage{previousParent, *this});
}

bool GameObject::operator==(const GameObject & gameObject) const {
    return id == gameObject.id;
}

bool GameObject::operator!=(const GameObject &gameObject) const {
    return !(*this == gameObject);
}
