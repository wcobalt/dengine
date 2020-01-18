#include <unordered_map>
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

using namespace dengine;

const unsigned Scene::BASE_NUMBERED_LAYERS_COUNT;
const unsigned Scene::DEFAULT_BASE_NUMBERED_LAYER;
const char Scene::BASE_NUMBERED_LAYER_PREFIX[] = "BaseNumberedLayer_";

Scene::Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior) : Scene(id, sceneBehavior, "") {}

Scene::Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior, const std::string &alias) : sceneBehavior(sceneBehavior),
                                                                                              id(id), alias(alias) {
    for (unsigned i = 0; i < BASE_NUMBERED_LAYERS_COUNT; i++) {
        std::shared_ptr<Layer> baseLayer(new Layer(BASE_NUMBERED_LAYER_PREFIX + std::to_string(i)));

        baseLayers.emplace_back(baseLayer);
    }
}

void Scene::sendMessage(MessageType messageType) {
    switch (messageType) {
        case MessageType::SCENE_LOAD:
            sceneBehavior->onSceneLoad(shared_from_this());

            break;
        case MessageType::SCENE_UNLOAD:
            handle(GameObject::MessageType::UPDATE);

            sceneBehavior->onSceneUnload(shared_from_this());
            freeScene();

            break;
        case MessageType::GAME_END:
            sceneBehavior->onGameEnd(shared_from_this());

            break;
        case MessageType::UPDATE:
            handle(GameObject::MessageType::UPDATE);

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

std::shared_ptr<GameObject> Scene::getRoot() const {
    return root;
}

const std::string &Scene::getAlias() const {
    return alias;
}

ID Scene::getId() const {
    return id;
}

void Scene::handle(GameObject::MessageType messageType) {
    std::unordered_map<ID, bool> hashTable;

    Filter filter(
    [messageType](std::shared_ptr<GameObject> gameObject) {
        gameObject->sendMessage(messageType);
    },

    [&hashTable](std::shared_ptr<GameObject> gameObject) -> bool {
        bool isActive = gameObject->getComponentsManager()->getComponent<TransformComponent>()->isActive();
        bool doIgnoreInactive = Dengine::get()->isIgnoringInactive();

        if (hashTable.find(gameObject->getId()) == hashTable.end() && (!doIgnoreInactive || isActive)) {
            hashTable.insert(std::make_pair(gameObject->getId(), true));

            return true;
        } else
            return false;
    }, false);

    filter.run(root);
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
