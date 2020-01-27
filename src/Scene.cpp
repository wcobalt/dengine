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

using namespace dengine;

Scene::Scene(ID id, SceneBehavior &sceneBehavior) : Scene(id, sceneBehavior, "") {}

Scene::Scene(ID id, SceneBehavior &sceneBehavior, const std::string &alias) : sceneBehavior(sceneBehavior),
                                                                              id(id), alias(alias) {}

void Scene::handleExternalEvent(EventType eventType) {
    switch (eventType) {
        case EventType::SCENE_LOAD:
            initializeSpaces();

            sceneBehavior.onSceneLoad(*this);

            break;
        case EventType::SCENE_UNLOAD:
            handle(GameObject::EventType::UPDATE);

            sceneBehavior.onSceneUnload(*this);
            freeScene();

            break;
        case EventType::GAME_END:
            sceneBehavior.onGameEnd(*this);

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
    std::set<ID> hashTable;

    BfsTraversal traversal;
    CustomFilter filter(
    [messageType](GameObject& gameObject, TraversalMethod& traversalMethod) {
        gameObject.handleExternalEvent(messageType);
    },

    [&hashTable](const GameObject& gameObject) -> bool {
        bool isActive = gameObject.getTransformComponent().isActive();
        bool doIgnoreInactive = Dengine::get().isIgnoringInactive();

        if (hashTable.find(gameObject.getId()) == hashTable.end() && (!doIgnoreInactive || isActive)) {
            hashTable.emplace(gameObject.getId());

            return true;
        } else
            return false;
    }, traversal);

    filter.run(*root);
}

void Scene::freeScene() {
    root->destroyAllChildren();
}

void Scene::initializeSpaces() {
    Space::reset();

    //WARNING & ATTENTION: YOU HAVE TO ADD
    standardSpaces.insert(std::make_pair(StandardSpace::SOME_SPACE, &Space::create("some_space")));
}

Space &Scene::getSpace(StandardSpace standardSpace) {
    return *standardSpaces.at(standardSpace);
}
