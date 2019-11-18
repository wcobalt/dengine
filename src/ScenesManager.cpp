#include "ScenesManager.h"
#include "Exceptions/SceneException.h"
#include "Scene.h"

using namespace dengine;

ScenesManager::ScenesManager() : currentId(1), currentScene(nullptr) {}

void ScenesManager::sendMessage(ScenesManagerMessage message) {
    if (isCurrentSceneExist()) {
        switch (message) {
            case ScenesManagerMessage::UPDATE:
                currentScene->getScene()->sendMessage(SceneMessage::UPDATE);

                break;
            case ScenesManagerMessage::GAME_END:
                currentScene->getScene()->sendMessage(SceneMessage::GAME_END);

                break;
        }
    }
}

ID ScenesManager::addScene(SceneBehavior &sceneBehavior) {
    return addScene(sceneBehavior, "");
}

ID ScenesManager::addScene(SceneBehavior &sceneBehavior, const std::string &alias) {
    std::shared_ptr<Scene> scene(new Scene(sceneBehavior));
    ID id = takeNextSceneId();

    std::shared_ptr<SceneEntry> sceneEntry(new SceneEntry(id, alias, scene));

    scenes.emplace_back(sceneEntry);

    return id;
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

ID ScenesManager::getCurrentSceneID() const {
    if (isCurrentSceneExist())
        return currentScene->getId();
    else
        throw SceneException("There is no current scene");
}

std::string ScenesManager::getCurrentSceneAlias() const {
    if (isCurrentSceneExist())
        return currentScene->getAlias();
    else
        throw SceneException("There is no current scene");
}

Scene &ScenesManager::getCurrentScene() const {
    if (isCurrentSceneExist())
        return *currentScene->getScene();
    else
        throw SceneException("There is no current scene");
}

bool ScenesManager::isCurrentSceneExist() const {
    return currentScene != nullptr;
}

Scene &ScenesManager::getScene(ID id) const {
    return *(*findSceneById(id))->getScene();
}

Scene &ScenesManager::getScene(const std::string &alias) const {
    return *(*findSceneByAlias(alias))->getScene();
}

ID ScenesManager::getIdByAlias(const std::string &alias) const {
    return (*findSceneByAlias(alias))->getId();
}

std::string ScenesManager::getAliasById(ID id) const {
    return (*findSceneById(id))->getAlias();
}

ID ScenesManager::takeNextSceneId() {
    return currentId++;
}

void ScenesManager::removeScene(decltype(scenes)::iterator iterator) {
    if ((*iterator)->getId() == currentScene->getId()) throw SceneException("Cannot remove current scene");

    scenes.erase(iterator);
}

ScenesManager::scene_iterator ScenesManager::findSceneByAlias(const std::string &alias) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if ((*it)->getAlias() == alias)
            return it;

    throw SceneException("There is no scene with such alias");
}

ScenesManager::scene_iterator ScenesManager::findSceneById(ID id) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if ((*it)->getId() == id)
            return it;

    throw SceneException("There is no scene with such id");
}

void ScenesManager::loadScene(scene_iterator iterator) {
    if (isCurrentSceneExist())
        currentScene->getScene()->sendMessage(SceneMessage::UNLOAD);

    currentScene = *iterator;
    currentScene->getScene()->sendMessage(SceneMessage::LOAD);
}

ScenesManager::SceneEntry::SceneEntry(ID id, const std::string &alias, std::shared_ptr<Scene> scene) : id(id), alias(alias),
    scene(scene) {}

ID ScenesManager::SceneEntry::getId() {
    return id;
}

std::string ScenesManager::SceneEntry::getAlias() {
    return alias;
}

std::shared_ptr<Scene> ScenesManager::SceneEntry::getScene() {
    return scene;
}
