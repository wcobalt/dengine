//
// Created by wcobalt on 1/27/20.
//

#include <algorithm>
#include "Space.h"
#include "GameObject.h"
#include "Components/Transform/TransformComponent.h"
#include "ComponentsManager.h"

using namespace dengine;

Space::Space(ID id, const std::string &name) : id(id), name(name) {}

Space::iterator Space::begin() {
    return gameObjects.begin();
}

Space::iterator Space::end() {
    return gameObjects.end();
}

Space::const_iterator Space::begin() const {
    return gameObjects.begin();
}

Space::const_iterator Space::end() const {
    return gameObjects.end();
}

Space::const_iterator Space::cbegin() {
    return gameObjects.cbegin();
}

Space::const_iterator Space::cend() {
    return gameObjects.cend();
}

ID Space::getId() const {
    return id;
}

const std::string &Space::getName() const {
    return name;
}

void Space::add(GameObject &gameObject) {
    if (findGameObject(gameObject) == gameObjects.end()) {
        gameObjects.emplace(&gameObject);

        gameObject.getComponentsManager().getTransformComponent().onAdditionToSpace(*this);
    }
}

void Space::remove(GameObject &gameObject) {
    auto it = findGameObject(gameObject);

    if (it != gameObjects.end()) {
        gameObjects.erase(it);

        gameObject.getComponentsManager().getTransformComponent().onRemovalFromSpace(*this);
    }
}

bool Space::has(GameObject &gameObject) const {
    return (gameObjects.find(&gameObject) != gameObjects.end());
}

Space::iterator Space::findGameObject(GameObject &gameObject) {
    return gameObjects.find(&gameObject);
}