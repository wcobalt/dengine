//
// Created by wcobalt on 1/27/20.
//

#include <algorithm>
#include "Space.h"
#include "GameObject.h"
#include "Components/Transform/TransformComponent.h"

using namespace dengine;

Space::Space(ID id, const std::string &name) : id(id), name(name) {}

Space &Space::create(const std::string &name) {
    class for_make_unique : public Space {
    public:
        for_make_unique(ID id, const std::string& name) : Space(id, name) {}
    };

    std::unique_ptr<Space> space = std::make_unique<for_make_unique>(takeNextId(), name);
    Space& spaceReference = *space;

    spaces->emplace(std::move(space));

    return spaceReference;
}

Space &Space::get(const std::string &name) {
    return **std::find_if(spaces->begin(), spaces->end(), [&name](const std::unique_ptr<Space>& space) {
        return space->getName() == name;
    });
}

Space &Space::get(ID id) {
    return **std::find_if(spaces->begin(), spaces->end(), [id](const std::unique_ptr<Space>& space) {
        return space->getId() == id;
    });
}

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

        gameObject.getTransformComponent().onAdditionToSpace(*this);
    }
}

void Space::remove(GameObject &gameObject) {
    auto it = findGameObject(gameObject);

    if (it != gameObjects.end()) {
        gameObjects.erase(it);

        gameObject.getTransformComponent().onRemovalFromSpace(*this);
    }
}

bool Space::has(GameObject &gameObject) const {
    return (gameObjects.find(&gameObject) != gameObjects.end());
}

Space::iterator Space::findGameObject(GameObject &gameObject) {
    return gameObjects.find(&gameObject);
}

ID Space::takeNextId() {
    return ++currentId;
}

void Space::reset() {
    currentId = IDUtils::NO_ID;

    spaces = std::make_unique<spaces_type>();
}
