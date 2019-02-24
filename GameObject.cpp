//
// Created by wcobalt on 19.09.18.
//

#include "GameObject.h"

GameObject::GameObject(unsigned int id):id(id) {

}

void GameObject::addChild(GameObject &child) {

}

void GameObject::addComponent(Component &component) {

}

void GameObject::removeComponent(std::string name) {

}

void GameObject::removeChild(unsigned int id) {

}

void GameObject::setParent(GameObject &parent) {

}

std::vector<Component&>& GameObject::getAllComponents() const {
    return *(new std::vector<Component&>(components));
}

std::vector<Component&> GameObject::getComponentsByID(const std::string& name) const {
    return components;
}

std::vector<GameObject&> GameObject::getChildren() const {

}

GameObject& GameObject::getParent() const {

}

unsigned int GameObject::getID() const {

}

std::vector<Component&> GameObject::hui() {

}