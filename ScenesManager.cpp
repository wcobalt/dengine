//
// Created by wcobalt on 3/30/19.
//

#include "ScenesManager.h"
#include "Events/EventsData.h"
#include "Events/MousePosition.h"
#include "Exceptions/NoCurrentSceneException.h"
#include "Exceptions/NoSuitableSceneException.h"
#include "Exceptions/CurrentSceneRemovingException.h"

using namespace dengine;
using namespace dengine::coreutils;
using namespace dengine::exceptions;

ScenesManager::ScenesManager():currentScene(NOT_EXIST_SCENE, nullptr) {
    nextSceneId = Dengine::MINIMAL_SAFE_ID;
}

void ScenesManager::update(DengineAccessor dengineAccessor) {
    if (currentScene.getID() != NOT_EXIST_SCENE) {
        currentScene.getObject()->update({});

        return;
    }

    throw NoCurrentSceneException();
}

ID ScenesManager::addScene(shared_ptr<Scene> scene) {
    return addScene(scene, "");
}

ID ScenesManager::addScene(shared_ptr<Scene> scene, String alias) {
    ID id = getUniqueSceneId();

    scenesIds.insert(std::pair<ID, Entry<String, Scene>>(id, Entry(alias, scene)));
    scenesAliases.insert(std::pair<String, Entry<ID, Scene>>(alias, Entry(id, scene)));

    return id;
}

void ScenesManager::loadScene(ID id) {
    auto it = scenesIds.find(id);

    if (it != scenesIds.end()) {
        setCurrentScene(Entry<ID, Scene>(id, it->second.getObject()));

        return;
    }

    throw NoSuitableSceneException();
}

void ScenesManager::loadScene(String alias) {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end()) {
        setCurrentScene(it->second);

        return;
    }

    throw NoSuitableSceneException();
}

void ScenesManager::removeScene(ID id) {
    if (id != currentScene.getID()) {
        auto it = scenesIds.find(id);

        if (it != scenesIds.end()) {
            scenesAliases.erase(it->second.getID());
            scenesIds.erase(it);

            return;
        }

        throw NoSuitableSceneException();
    }

    throw CurrentSceneRemovingException();
}

void ScenesManager::removeScene(String alias) {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end()) {
        ID id = it->second.getID();

        if (id != currentScene.getID()) {
            scenesIds.erase(id);
            scenesAliases.erase(it);

            return;
        }

        throw CurrentSceneRemovingException();
    }

    throw NoSuitableSceneException();
}

void ScenesManager::setCurrentScene(Entry<ID, Scene> scene) {
    if (currentScene.getID() != NOT_EXIST_SCENE)
        currentScene.getObject()->destroy({});

    currentScene = scene;

    currentScene.getObject()->create({});
}

shared_ptr<Scene> ScenesManager::getScene(ID id) const {
    auto it = scenesIds.find(id);

    if (it != scenesIds.end())
        return it->second.getObject();

    throw NoSuitableSceneException();
}

shared_ptr<Scene> ScenesManager::getScene(String alias) const {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end())
        return it->second.getObject();

    throw NoSuitableSceneException(); //may be better return NOT_EXIST_SCENE?
}

ID ScenesManager::getCurrentSceneID() const {
    if (currentScene.getID() != NOT_EXIST_SCENE)
        return currentScene.getID();

    throw NoCurrentSceneException();
}

shared_ptr<Scene> ScenesManager::getCurrentScene() const {
    if (currentScene.getID() != NOT_EXIST_SCENE)
        return currentScene.getObject();

    throw NoCurrentSceneException();
}

ID ScenesManager::getIDByAlias(String alias) const {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end())
        return it->second.getID();

    throw NoSuitableSceneException();
}

String ScenesManager::getAliasByID(ID id) const {
    auto it = scenesIds.find(id);

    if (it != scenesIds.end())
        return it->second.getID();

    throw NoSuitableSceneException();
}

ID ScenesManager::getUniqueSceneId() {
    return nextSceneId++;
}