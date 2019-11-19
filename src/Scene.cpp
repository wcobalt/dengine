#include <unordered_map>
#include "Scene.h"
#include "SceneBehavior.h"
#include "GameObject.h"
#include "Filter/Filter.h"

using namespace dengine;

Scene::Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior) : Scene(id, sceneBehavior, "") {}

Scene::Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior, const std::string &alias) : sceneBehavior(sceneBehavior),
                                                                                              id(id), alias(alias) {}

void Scene::sendMessage(SceneMessage message) {
    switch (message) {
        case SceneMessage::LOAD:
            sceneBehavior->onSceneLoad(*this);

            break;
        case SceneMessage::UNLOAD:
            handle([](auto gameObject) {
                gameObject->sendMessage(GameObjectMessage::SCENE_UNLOAD);
            });

            sceneBehavior->onSceneUnload(*this);

            break;
        case SceneMessage::GAME_END:
            handle([](auto gameObject) {
                gameObject->sendMessage(GameObjectMessage::GAME_END);
            });

            sceneBehavior->onGameEnd(*this);

            break;
        case SceneMessage::UPDATE:
            handle([](auto gameObject) {
                gameObject->sendMessage(GameObjectMessage::UPDATE);
            });

            break;
    }
}

ID Scene::takeNextId() {
    return currentId++;
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

void Scene::handle(std::function<void (std::shared_ptr<GameObject>)> handler) {
    std::unordered_map<ID, bool> hashTable;

    Filter filter(handler, [&hashTable](std::shared_ptr<GameObject> gameObject) -> bool {
        if (hashTable.find(gameObject->getId()) == hashTable.end()) {
            hashTable.insert(std::make_pair(gameObject->getId(), true));

            return true;
        } else
            return false;
    });
}
