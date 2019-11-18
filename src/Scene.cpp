
#include "Scene.h"
#include "SceneBehavior.h"

using namespace dengine;

Scene::Scene(SceneBehavior &sceneBehavior) : sceneBehavior(sceneBehavior), currentId(1) {
    root = std::make_shared<GameObject>();
}

void Scene::sendMessage(SceneMessage message) {
    switch (message) {
        case SceneMessage::LOAD:
            sceneBehavior.onSceneLoad(*this);

            //delegate to objects
            break;
        case SceneMessage::UNLOAD:
            //delegate to objects
            sceneBehavior.onSceneUnload(*this);

            break;
        case SceneMessage::GAME_END:
            //delegate to objects
            sceneBehavior.onGameEnd(*this);

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