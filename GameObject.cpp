//
// Created by wcobalt on 19.09.18.
//

#include "GameObject.h"
#include "Exceptions/NoSuitableComponentException.h"

using namespace dengine;
using namespace dengine::components;
using namespace dengine::exceptions;

GameObject::GameObject(shared_ptr<Transform3DComponent> transform) {
    addComponent(std::dynamic_pointer_cast<Component>(transform));
}

void GameObject::addComponent(shared_ptr<Component> component) {
    //two components of one type problem!
    components.push_back(component);

    component->componentLoad(*this);
}

template <class T>
void GameObject::removeComponent() {
    for (auto it = components.begin(); it != components.end(); it++) {
        if (std::dynamic_pointer_cast<T>(*it)) {
            removeComponent(it);

            return;
        }
    }

    throw NoSuitableComponentException();
}

void GameObject::removeComponent(shared_ptr<Component> component) {
    for (auto it = components.begin(); it != components.end(); it++) {
        if (*it == component) {
            removeComponent(it);

            return;
        }
    }

    throw NoSuitableComponentException();
}

void GameObject::removeComponent(vector<shared_ptr<Component>>::iterator it) {
    (*it)->componentUnload();

    components.erase(it);
}

void GameObject::addChild(shared_ptr<GameObject> instance) {

}

void GameObject::removeChild(shared_ptr<GameObject> instance) {

}

void GameObject::removeAllChildren() {
    for (shared_ptr<GameObject>& child : children)
        removeChild(child);
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

    throw NoSuitableComponentException();
}

vector<shared_ptr<Component>> GameObject::getAllComponents() const {
    return components;
}