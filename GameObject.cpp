//
// Created by wcobalt on 19.09.18.
//

#include "GameObject.h"

std::vector<Component*>* GameObject::getAllComponents() {
    std::vector<Component*> result = components;

    return &result;
}

std::vector<Component*>* GameObject::getComponentsByName(std::string name) {
    std::vector<Component*> result;

    unsigned long size = components.size();

    for(unsigned long i = 0; i < size; i++) {
        if(components[i].getID() == name) result.push_back(components[i]);
    }

    return &result;
}

std::vector<Component*>* GameObject::getComponentsByGroup(std::string group) {

}

void GameObject::addComponent(Component component) {

}

void GameObject::setParent(GameObject* parent) {

}

void GameObject::addChild(std::vector<GameObject*> children) {

}

GameObject* GameObject::getParent() {

}

std::vector<GameObject*>* GameObject::getChildren() {

}

ID* GameObject::getID() {

}