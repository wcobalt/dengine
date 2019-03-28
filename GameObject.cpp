//
// Created by wcobalt on 19.09.18.
//

#include "GameObject.h"

using namespace dengine;
using namespace dengine::components;

GameObject::GameObject(uint id):id(id) {

}

void GameObject::addChild(GameObject &child) {

}

void GameObject::addComponent(Component &component) {

}

void GameObject::removeComponent(const std::string& name) {

}

void GameObject::removeChild(uint id) {

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

uint GameObject::getID() const {

}