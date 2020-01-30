#include "ScenesManager.h"
#include "Exceptions/SceneException.h"
#include "Scene.h"
#include "Space.h"
#include "Exceptions/IllegalArgumentException.h"

using namespace dengine;

void ScenesManager::handleExternalEvent(EventType eventType) {
    if (isAnySceneLoaded()) {
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

Scene & ScenesManager::addScene(std::unique_ptr<SceneBehavior> sceneBehavior) {
    return addScene(std::move(sceneBehavior), "");
}

Scene & ScenesManager::addScene(std::unique_ptr<SceneBehavior> sceneBehavior, std::string alias) {
    auto it = !alias.empty() ? findSceneByAlias(alias) : scenes.end();

    if (it == scenes.end()) {
        ID id = takeNextSceneId();
        std::unique_ptr<Scene> scene = std::make_unique<Scene>(id, std::move(sceneBehavior), std::move(alias));

        Scene& sceneReference = *scene;

        scenes.emplace_back(std::move(scene));

        return sceneReference;
    } else
        throw IllegalArgumentException("Cannot create new scene: there is already a scene with alias '" + alias + "'");
}

void ScenesManager::removeScene(ID id) {
    auto it = findSceneById(id);

    if (it != scenes.end())
        removeScene(it);
    else
        throw IllegalArgumentException("Unable to remove scene: there's no scene with id " + std::to_string(id));
}

void ScenesManager::removeScene(std::string_view alias) {
    auto it = findSceneByAlias(alias);

    if (it != scenes.end())
        removeScene(it);
    else
        throw IllegalArgumentException("Unable to remove scene: there's no scene with alias '" + std::string(alias) + "'");
}

void ScenesManager::removeScene(Scene &scene) {
    removeScene(scene.getId());
}

void ScenesManager::loadScene(ID id) {
    auto it = findSceneById(id);

    if (it != scenes.end())
        loadScene(it);
    else
        throw IllegalArgumentException("Unable to load scene: there's no scene with id " + std::to_string(id));
}

void ScenesManager::loadScene(std::string_view alias) {
    auto it = findSceneByAlias(alias);

    if (it != scenes.end())
        loadScene(it);
    else
        throw IllegalArgumentException("Unable to load scene: there's no scene with alias '" + std::string(alias) + "'");
}

void ScenesManager::loadScene(Scene &scene) {
    //maybe it shouldn't resolve in iterator, but it's protecting from load of nonexistent scene

    loadScene(scene.getId());
}

void ScenesManager::restartScene() {
    if (isAnySceneLoaded())
        loadScene(currentScene->getId());
    else
        throw SceneException("Cannot restart scene: there is no current scene");
}

void ScenesManager::loadNextScene() {
    if (isAnySceneLoaded()) {
        auto it = findSceneById(currentScene->getId());

        if (scenes.end() - it > 1)
            loadScene(it + 1);
        else
            throw SceneException("Cannot load the next scene, because current scene is the last one");
    } else
        throw SceneException("Cannot load the next scene, because there is no current one");
}

void ScenesManager::loadPreviousScene() {
    if (isAnySceneLoaded()) {
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

Scene & ScenesManager::getCurrentScene() const {
    if (isAnySceneLoaded())
        return *currentScene;
    else
        throw SceneException("There is no current scene");
}

bool ScenesManager::isAnySceneLoaded() const {
    return currentScene != nullptr;
}

Scene & ScenesManager::getScene(ID id) const {
    auto it = findSceneById(id);

    if (it != scenes.end())
        return **it;
    else
        throw IllegalArgumentException("Unable to find scene: there's no scene with id " + std::to_string(id));
}

Scene & ScenesManager::getScene(std::string_view alias) const {
    if (!alias.empty()) {
        auto it = findSceneByAlias(alias);

        if (it != scenes.end())
            return **it;
        else
            throw IllegalArgumentException("Unable to find scene: there's no scene with alias '" + std::string(alias) + "'");
    } else
        throw IllegalArgumentException("Scene's alias string cannot be empty");
}

ID ScenesManager::takeNextSceneId() {
    return currentId++;
}

void ScenesManager::removeScene(const_iterator iterator) {
    if ((*iterator)->getId() == currentScene->getId())
        throw SceneException("Cannot remove current scene");

    scenes.erase(iterator);
}

ScenesManager::iterator ScenesManager::findSceneByAlias(std::string_view alias) const {
    return std::find_if(scenes.begin(), scenes.end(), [alias](const std::unique_ptr<Scene>& scene) {
        return alias == scene->getAlias();
    });
}

ScenesManager::iterator ScenesManager::findSceneById(ID id) const {
    return std::find_if(scenes.begin(), scenes.end(), [id](const std::unique_ptr<Scene>& scene) {
        return id == scene->getId();
    });
}

void ScenesManager::loadScene(const_iterator iterator) {
    unloadCurrentScene();

    //isn't it risky? (relative to dengine which may be doing something with current scene at the moment)
    currentScene = &**iterator;
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
