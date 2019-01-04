//
// Created by wcobalt on 19.09.18.
//

#include "GameObject.h"

const std::vector<const Component *const> *const GameObject::getAllComponents() {
    return &components;
}

const std::vector<const Component *const> *const GameObject::getComponentsByName(std::string name) {
    const std::vector<const Component *const> *const result = new std::vector<const Component *const>();

    unsigned long size = components.size();

    for(unsigned long i = 0; i < size; i++) {
        if(components[i]->getID()->getName() == name) result.push_back(components[i]);
    }

    return result;
}

const std::vector<const Component *const> *const GameObject::getComponentsByGroup(std::string group) {
    const std::vector<const Component *const> *const result = new std::vector<const Component *const>();

    unsigned long size = components.size();

    for(unsigned long i = 0; i < size; i++) {
        if(components[i]->getID()->getGroup() == group) result.push_back(components[i]);
    }

    return result;
}

void GameObject::addComponent(Component *component) {
    components.push_back(component);
}

void GameObject::setParent(GameObject *parent) {
    this->parent = parent;
}

void GameObject::addChild(std::vector<GameObject*> children) {
    this->children.insert(this->children.end(), children.begin(), children.end());
}

GameObject *GameObject::getParent() {
    return parent;
}

const std::vector<GameObject*> GameObject::getChildren() {
    return children;
}

ID *GameObject::getID() {
    return id;
}