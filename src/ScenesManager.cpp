//
// Created by wcobalt on 3/30/19.
//

#include <map>
#include <memory>
#include <string>

#include "ScenesManager.h"
#include "Dengine.h"
#include "Coreutils/ID.h"
#include "Scene.h"
#include "DengineAccessor.h"
#include "Exceptions/NoCurrentSceneException.h"
#include "Exceptions/NoSuitableSceneException.h"
#include "Exceptions/CurrentSceneRemovingException.h"

using std::shared_ptr;
using std::string;

using namespace dengine;

ScenesManager::ScenesManager():currentScene(NOT_EXIST_SCENE, nullptr), nextSceneId(Dengine::MINIMAL_SAFE_ID) {}

void ScenesManager::update(const DengineAccessor& dengineAccessor) {
    if (currentScene.first != NOT_EXIST_SCENE) {
        currentScene.second->update(dengineAccessor);

        return;
    }

    throw NoCurrentSceneException();
}

ID ScenesManager::addScene(shared_ptr<Scene> scene) {
    return addScene(scene, "");
}

ID ScenesManager::addScene(shared_ptr<Scene> scene, const string& alias) {
    ID id = getUniqueSceneId();

    scenesIds.insert(std::make_pair(id, std::make_pair(alias, scene)));
    scenesAliases.insert(std::make_pair(alias, std::make_pair(id, scene)));

    return id;
}

void ScenesManager::loadScene(ID id) {
    auto it = scenesIds.find(id);

    if (it != scenesIds.end()) {
        setCurrentScene(std::make_pair(id, it->second.second));

        return;
    }

    throw NoSuitableSceneException();
}

void ScenesManager::loadScene(const string& alias) {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end()) {
        setCurrentScene(it->second);

        return;
    }

    throw NoSuitableSceneException();
}

void ScenesManager::removeScene(ID id) {
    if (id != currentScene.first) {
        auto it = scenesIds.find(id);

        if (it != scenesIds.end()) {
            scenesAliases.erase(it->second.first);
            scenesIds.erase(it);

            return;
        }

        throw NoSuitableSceneException();
    }

    throw CurrentSceneRemovingException();
}

void ScenesManager::removeScene(const string& alias) {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end()) {
        ID id = it->second.first;

        if (id != currentScene.first) {
            scenesIds.erase(id);
            scenesAliases.erase(it);

            return;
        }

        throw CurrentSceneRemovingException();
    }

    throw NoSuitableSceneException();
}

void ScenesManager::setCurrentScene(std::pair<ID, shared_ptr<Scene>> scene) {
    DengineAccessor key;

    if (currentScene.first != NOT_EXIST_SCENE)
        currentScene.second->destroy(key);

    currentScene.first = scene.first;
    currentScene.second = scene.second;

    currentScene.second->create(key);
}

shared_ptr<Scene> ScenesManager::getScene(ID id) const {
    auto it = scenesIds.find(id);

    if (it != scenesIds.end())
        return it->second.second;

    throw NoSuitableSceneException();
}

shared_ptr<Scene> ScenesManager::getScene(const string& alias) const {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end())
        return it->second.second;

    throw NoSuitableSceneException();
}

ID ScenesManager::getCurrentSceneID() const {
    if (currentScene.first != NOT_EXIST_SCENE)
        return currentScene.first;

    throw NoCurrentSceneException();
}

shared_ptr<Scene> ScenesManager::getCurrentScene() const {
    if (currentScene.first != NOT_EXIST_SCENE)
        return currentScene.second;

    throw NoCurrentSceneException();
}

ID ScenesManager::getIDByAlias(const string& alias) const {
    auto it = scenesAliases.find(alias);

    if (it != scenesAliases.end())
        return it->second.first;

    throw NoSuitableSceneException();
}

string ScenesManager::getAliasByID(ID id) const {
    auto it = scenesIds.find(id);

    if (it != scenesIds.end())
        return it->second.first;

    throw NoSuitableSceneException();
}

ID ScenesManager::getUniqueSceneId() {
    return nextSceneId++;
}