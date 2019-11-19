
#include "Scene.h"
#include "SceneBehavior.h"

using namespace dengine;

Scene::Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior) : Scene(id, std::move(sceneBehavior), "") {}

Scene::Scene(ID id, std::shared_ptr<SceneBehavior> sceneBehavior, const std::string &alias) : sceneBehavior(std::move(sceneBehavior)),
                                                                                              id(id), alias(alias) {}

void Scene::sendMessage(SceneMessage message) {
    switch (message) {
        case SceneMessage::LOAD:
            sceneBehavior->onSceneLoad(*this);

            //delegate to objects
            break;
        case SceneMessage::UNLOAD:
            //delegate to objects
            sceneBehavior->onSceneUnload(*this);

            break;
        case SceneMessage::GAME_END:
            //delegate to objects
            sceneBehavior->onGameEnd(*this);

            break;
        case SceneMessage::UPDATE:
            //delegate to objects
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
