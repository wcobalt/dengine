#include <set>
#include <memory>
#include "Scene.h"
#include "SceneBehavior.h"
#include "GameObject.h"
#include "Filter/Filter.h"
#include "Dengine.h"
#include "Components/Transform/TransformComponent.h"
#include "Layer.h"
#include "Exceptions/SceneException.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "ComponentsManager.h"
#include "Filter/CustomFilter.h"
#include "Filter/TraversalMethods/BfsTraversal.h"

using namespace dengine;

const unsigned Scene::BASE_NUMBERED_LAYERS_COUNT;
const unsigned Scene::DEFAULT_BASE_NUMBERED_LAYER;
const char Scene::BASE_NUMBERED_LAYER_PREFIX[] = "BaseNumberedLayer_";

Scene::Scene(ID id, SceneBehavior &sceneBehavior) : Scene(id, sceneBehavior, "") {}

Scene::Scene(ID id, SceneBehavior &sceneBehavior, const std::string &alias) : sceneBehavior(sceneBehavior),
                                                                              id(id), alias(alias) {
    for (unsigned i = 0; i < BASE_NUMBERED_LAYERS_COUNT; i++) {
        //@todo add layer manager
//        std::shared_ptr<Layer> baseLayer(new Layer(BASE_NUMBERED_LAYER_PREFIX + std::to_string(i)));
//
//        baseLayers.emplace_back(baseLayer);
    }
}

void Scene::handleExternalEvent(EventType eventType) {
    switch (eventType) {
        case EventType::SCENE_LOAD:
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

std::shared_ptr<Layer> Scene::getBaseLayerByName(const std::string &layerName) const {
    auto it = findLayer(layerName);

    if (it != baseLayers.end())
        return *it;
    else
        throw SceneException("Unable to find layer with such name: " + layerName);
}

std::shared_ptr<Layer> Scene::getBaseNumberedLayer(unsigned number) const {
    return getBaseLayerByName(BASE_NUMBERED_LAYER_PREFIX + std::to_string(number));
}

std::shared_ptr<Layer> Scene::getDefaultBaseNumberedLayer() const {
    return baseLayers[DEFAULT_BASE_NUMBERED_LAYER];
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
        bool isActive = gameObject.getComponentsManager().getComponent<TransformComponent>().isActive();
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

Scene::const_layer_iterator Scene::findLayer(const std::string &layerName) const {
    for (auto it = baseLayers.begin(); it != baseLayers.end(); it++) {
        if ((*it)->toString() == layerName) return it;
    }

    return baseLayers.end();
}
