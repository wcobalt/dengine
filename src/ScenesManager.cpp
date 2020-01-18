#include "ScenesManager.h"
#include "Exceptions/SceneException.h"
#include "Scene.h"

using namespace dengine;

ScenesManager::ScenesManager() : currentId(1), currentScene(nullptr) {}

void ScenesManager::handleExternalEvent(EventType eventType) {
    if (isCurrentSceneExist()) {
        switch (eventType) {
            case EventType::UPDATE:
                currentScene->handleExternalEvent(Scene::EventType::UPDATE);

                break;
            case EventType::GAME_END:
                currentScene->handleExternalEvent(Scene::EventType::GAME_END);
                unloadCurrentScene();

                break;
        }
    }
}

ID ScenesManager::addScene(std::shared_ptr<SceneBehavior> sceneBehavior) {
    return addScene(std::move(sceneBehavior), "");
}

ID ScenesManager::addScene(std::shared_ptr<SceneBehavior> sceneBehavior, const std::string &alias) {
    auto it = findSceneByAlias(alias);

    if (it == scenes.end()) {
        ID id = takeNextSceneId();
        std::shared_ptr<Scene> scene(new Scene(id, sceneBehavior, alias));

        scenes.emplace_back(scene);

        return id;
    } else
        throw SceneException("Cannot create new scene: there is a scene with such alias already");
}

void ScenesManager::removeScene(ID id) {
    removeScene(findSceneById(id));
}

void ScenesManager::removeScene(const std::string &alias) {
    removeScene(findSceneByAlias(alias));
}

void ScenesManager::loadScene(ID id) {
    loadScene(findSceneById(id));
}

void ScenesManager::loadScene(const std::string &alias) {
    loadScene(findSceneByAlias(alias));
}

void ScenesManager::restartScene() {
    if (isCurrentSceneExist())
        loadScene(currentScene->getId());
    else
        throw SceneException("Cannot restart scene. There is no current scene");
}

void ScenesManager::loadNextScene() {
    if (isCurrentSceneExist()) {
        auto it = findSceneById(currentScene->getId());

        if (scenes.end() - it > 1)
            loadScene(it + 1);
        else
            throw SceneException("Cannot load the next scene, because current scene is the last one");
    } else
        throw SceneException("Cannot load the next scene, because there is no current one");
}

void ScenesManager::loadPreviousScene() {
    if (isCurrentSceneExist()) {
        auto it = findSceneById(currentScene->getId());

        if (it > scenes.begin())
            loadScene(it - 1);
        else
            throw SceneException("Cannot load the previous scene, because current scene is the first one");
    } else
        throw SceneException("Cannot load the previous scene, because there is no current one");
}

void ScenesManager::loadFirstScene() {
    if (!scenes.empty())
        loadScene(scenes.begin());
    else
        throw SceneException("Cannot load first scene, because there are no scenes");
}

std::shared_ptr<Scene> ScenesManager::getCurrentScene() const {
    if (isCurrentSceneExist())
        return currentScene;
    else
        throw SceneException("There is no current scene");
}

bool ScenesManager::isCurrentSceneExist() const {
    return currentScene != nullptr;
}

std::shared_ptr<Scene> ScenesManager::getScene(ID id) const {
    return *findSceneById(id);
}

std::shared_ptr<Scene> ScenesManager::getScene(const std::string &alias) const {
    return *findSceneByAlias(alias);
}

ID ScenesManager::takeNextSceneId() {
    return currentId++;
}

void ScenesManager::removeScene(const_iterator iterator) {
    if ((*iterator)->getId() == currentScene->getId()) throw SceneException("Cannot remove current scene");

    scenes.erase(iterator);
}

ScenesManager::const_iterator ScenesManager::findSceneByAlias(const std::string &alias) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if ((*it)->getAlias() == alias)
            return it;

    throw SceneException("There is no scene with such alias");
}

ScenesManager::const_iterator ScenesManager::findSceneById(ID id) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if ((*it)->getId() == id)
            return it;

    throw SceneException("There is no scene with such id");
}

void ScenesManager::loadScene(const_iterator iterator) {
    unloadCurrentScene();

    currentScene = *iterator;
    currentScene->handleExternalEvent(Scene::EventType::SCENE_LOAD);
}

ScenesManager::iterator ScenesManager::begin() {
    return scenes.begin();
}

ScenesManager::iterator ScenesManager::end() {
    return scenes.end();
}

ScenesManager::const_iterator ScenesManager::begin() const {
    return scenes.cbegin();
}

ScenesManager::const_iterator ScenesManager::end() const {
    return scenes.cend();
}

ScenesManager::const_iterator ScenesManager::cbegin() const {
    return scenes.cbegin();
}

ScenesManager::const_iterator ScenesManager::cend() const {
    return scenes.cend();
}

void ScenesManager::unloadCurrentScene() {
    if (currentScene != nullptr) {
        currentScene->handleExternalEvent(Scene::EventType::SCENE_UNLOAD);

        currentScene = nullptr;
    }
}
