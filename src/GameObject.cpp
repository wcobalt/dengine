//
// Created by wcobalt on 19.09.18.
//

#include <vector>
#include <string>
#include <memory>

#include "GameObject.h"
#include "Scene.h"
#include "ScenesManager.h"
#include "Dengine.h"
#include "Components/Component.h"
#include "Components/TransformComponent.h"
#include "Exceptions/ComponentException.h"

using namespace dengine;

using std::shared_ptr;
using std::vector;

GameObject::GameObject():GameObject(std::make_shared<TransformComponent>()) {}

GameObject::GameObject(shared_ptr<TransformComponent> transform) {
    addComponent(std::dynamic_pointer_cast<Component>(transform));

    initParent();
}

void GameObject::initParent() {
    parent = Dengine::get()->getScenesManager()->getCurrentScene()->getRoot();
}

void GameObject::addComponent(shared_ptr<Component> component) {
    for (shared_ptr<GameObject>& currentComponent : children) {
        if (typeid(currentComponent).hash_code() == typeid(component).hash_code())
            throw ComponentException("The component is already bound to this game object");
    }

    components.push_back(component);

    shared_ptr<GameObject> th(this);

    component->onComponentLoad({}, th);
}
//@todo think about weak_ptr
//only if T has default constructor
//SFINAE
template <class T>
void GameObject::addComponent() {
    shared_ptr<T> object = std::make_shared<T>();
    shared_ptr<Component> component = std::dynamic_pointer_cast<Component>(object);//exceptionable

    if (component)
        addComponent(component);
    else
        throw ComponentException("T type is not an exception type");
}

template <class T>
void GameObject::removeComponent() {
    for (auto it = components.begin(); it != components.end(); it++) {
        if (std::dynamic_pointer_cast<T>(*it)) {
            safelyRemoveComponent(it);

            return;
        }
    }

    throw ComponentException("No such component was found");
}

void GameObject::removeComponent(shared_ptr<Component> component) {
    for (auto it = components.begin(); it != components.end(); it++) {
        if (*it == component) {
            safelyRemoveComponent(it);

            return;
        }
    }

    throw ComponentException("No such component was found");
}

void GameObject::safelyRemoveComponent(vector<shared_ptr<Component>>::iterator it) {
    if (!std::dynamic_pointer_cast<TransformComponent>(*it))
        removeComponent(it);
    else
        throw ComponentException("Unable to remove Transform Component");
}

void GameObject::removeComponent(vector<shared_ptr<Component>>::iterator it) {
    (*it)->onComponentUnload({});

    components.erase(it);
}

//@todo may be add events of removeing/adding child in component
//@todo several identical children, may be add flag - checkRepeatings which will be to check fucking repeatings of children?
void GameObject::addChild(shared_ptr<GameObject> instance) {
    children.push_back(instance);

    instance->parent = shared_ptr<GameObject>(this);
}

void GameObject::removeChild(shared_ptr<GameObject> instance) {
    for (auto it = children.begin(); it != children.end(); it++)
        if (*it == instance)
            removeChild(it);
}

void GameObject::removeAllChildren() {
    for (auto it = children.begin(); it != children.end(); it++)
        removeChild(it);
}

void GameObject::removeChild(vector<shared_ptr<GameObject>>::iterator it) {
    (*it)->parent = Dengine::get()->getScenesManager()->getCurrentScene()->getRoot();

    children.erase(it);
}

shared_ptr<GameObject> GameObject::getParent() const {
    return parent;
}

vector<shared_ptr<GameObject>> GameObject::getChildren() const {
    return children;
}

template <class T>
shared_ptr<T> GameObject::getComponent() const {
    for (auto it = components.begin(); it != components.end(); it++) {
        shared_ptr<T> component = std::dynamic_pointer_cast<T>(*it);

        if (component)
            return component;
    }

    throw ComponentException("No such component was found");
}

vector<shared_ptr<Component>> GameObject::getAllComponents() const {
    return components;
}

void GameObject::create() {
    for (shared_ptr<Component>& component : components)
        component->oInstanceCreate(dengineAccessor);
}

void GameObject::destroy(, bool isSceneUnloading) {
    for (auto it = components.begin(); it != components.end(); it++) {
        if (isSceneUnloading) {
            shared_ptr<Component> component = *it;

            removeComponent(it);

            component->onInstanceDestroy(dengineAccessor);
        } else
            removeComponent(it);
    }

    removeAllChildren();

    getParent()->removeChild(shared_ptr<GameObject>(this));
}

void GameObject::update() {
    for (shared_ptr<Component>& component : components)
        component->onUpdate(dengineAccessor);
}