#include <set>
#include <memory>
#include "Scene.h"
#include "SceneBehavior.h"
#include "GameObject.h"
#include "Filter/Filter.h"
#include "Dengine.h"
#include "Components/Transform/TransformComponent.h"
#include "Exceptions/SceneException.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "ComponentsManager.h"
#include "Filter/CustomFilter.h"
#include "Filter/TraversalMethods/BfsTraversal.h"
#include "Space.h"
#include "SpacesManager.h"

using namespace dengine;

Scene::Scene(ID id, std::unique_ptr<SceneBehavior> sceneBehavior) : Scene(id, std::move(sceneBehavior), "") {}

Scene::Scene(ID id, std::unique_ptr<SceneBehavior> sceneBehavior, const std::string &alias) : sceneBehavior(std::move(sceneBehavior)),
                                                                                              id(id), alias(alias),
                                                                                              spacesManager(std::make_unique<SpacesManager>()) {}

void Scene::handleExternalEvent(EventType eventType) {
    switch (eventType) {
        case EventType::SCENE_LOAD:
            initializeSpaces();

            sceneBehavior->onSceneLoad(*this);

            break;
        case EventType::SCENE_UNLOAD:
            handle(GameObject::EventType::SCENE_UNLOAD);

            sceneBehavior->onSceneUnload(*this);
            freeScene();

            break;
        case EventType::GAME_END:
            sceneBehavior->onGameEnd(*this);
            handle(GameObject::EventType::GAME_END);

            break;
        case EventType::UPDATE:
            handle(GameObject::EventType::UPDATE);

            break;
    }
}

ID Scene::takeNextId() {
    return currentId++;
}

GameObject & Scene::getRoot() const {
    return *root;
}

const std::string &Scene::getAlias() const {
    return alias;
}

ID Scene::getId() const {
    return id;
}

void Scene::handle(GameObject::EventType messageType) {
    std::set<ID> hashTable;//it's not a hashtable

    BfsTraversal traversal;
    CustomFilter filter(
    [messageType](GameObject& gameObject, TraversalMethod& traversalMethod) {
        gameObject.handleExternalEvent(messageType);
    },

    [&hashTable](const GameObject& gameObject) -> bool {
        bool isActive = gameObject.getTransformComponent().isActive();

        hashTable.emplace(gameObject.getId());

        return hashTable.find(gameObject.getId()) == hashTable.end() && isActive;
    }, traversal);

    filter.run(*root);
}

void Scene::freeScene() {
    root->destroyAllChildren();
    spacesManager->clear();
}

void Scene::initializeSpaces() {
    standardSpaces.insert(std::make_pair(StandardSpace::SOME_SPACE, &spacesManager->create("some_space")));
}

SpacesManager &Scene::getSpaces() const {
    return *spacesManager;
}

Space &Scene::getSpace(StandardSpace standardSpace) const {
    return *standardSpaces.at(standardSpace);
}

SceneBehavior &Scene::getBehavior() const {
    return *sceneBehavior;
}
