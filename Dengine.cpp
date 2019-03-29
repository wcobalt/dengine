//
// Created by wcobalt on 16.09.18.
//

#include "Dengine.h"
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include "Events/EventsData.h"
#include "Events/MousePosition.h"
#include "Exceptions/NoCurrentSceneException.h"
#include "Exceptions/NoSuitableSceneException.h"
#include "Exceptions/CurrentSceneRemovingException.h"

using namespace dengine;
using namespace dengine::exceptions;
using namespace dengine::coreutils;

Dengine::Dengine(std::shared_ptr<WindowManager> windowManager) {
    setWindowManager(windowManager);

    mIsPaused = false;
    isGameStopped = false;
    nextSceneId = 3;
}

void Dengine::update() {
    std::shared_ptr<const EventsData> data = windowManager->getWindowAccessor()->checkEvents();
}

void Dengine::setFPS(float fps) {
    this->fps = fps;
}

void Dengine::setWindowManager(std::shared_ptr<WindowManager> windowManager) {
    this->windowManager = windowManager;
}

void Dengine::run() {
    isGameStopped = false;

    while (!isGameStopped) {
        std::future fut = std::async(&Dengine::update, *this);

        //@todo async may take some time real_fps != fps
        std::this_thread::sleep_for(std::chrono::milliseconds((int) (1000.0 / fps)));
    }
}

void Dengine::setPaused(bool isPaused) {
    mIsPaused = isPaused;
}

void Dengine::stop() {
    isGameStopped = true;
}

ID Dengine::addScene(std::shared_ptr<Scene> scene) {
    std::shared_ptr<Entry<Scene>> newScene;

    ID id = getUniqueSceneId();

    newScene = std::make_shared<Entry<Scene>>(new Entry<Scene>(scene, id));

    scenes.push_back(newScene);

    scenes[0]->getObject();

    return id;
}

ID Dengine::addScene(std::shared_ptr<Scene> scene, String alias) {
    ID id = addScene(scene);

    aliases.insert(aliases.end(), std::pair<String, ID>(alias, id));
}

void Dengine::loadScene(ID id) {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if ((*it)->getID() == id) {
            currentScene = id;

            //
            return;
        }

    throw NoSuitableSceneException();
}

void Dengine::loadScene(String alias) {

}

void Dengine::removeScene(ID id) {
    if (id != currentScene) {
        for (auto it = scenes.begin(); it != scenes.end(); it++)
            if (it->get()->getID() == id) {

                //

                return;
            }

        throw NoSuitableSceneException();
    }

    throw CurrentSceneRemovingException();
}

void Dengine::removeScene(String alias) {

}

std::shared_ptr<Scene> Dengine::getScene(ID id) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if ((*it)->getID() == id)
            return it->get()->getObject();

    throw NoSuitableSceneException();
}

shared_ptr<Scene> Dengine::getScene(String alias) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if (it->get()->getID() == id &&)
            return it->get()->getObject();

    throw NoSuitableSceneException();
}

ID Dengine::getCurrentScene() const {
    if (currentScene != 0)
        return currentScene;

    throw NoCurrentSceneException();
}

std::shared_ptr<WindowManager> Dengine::getWindowManager() const {
    return windowManager;
}

float Dengine::getFPS() const {
    return fps;
}

bool Dengine::isPaused() const {
    return mIsPaused;
}

ID Dengine::getIDByAlias(String alias) const {
    auto it = aliases.find(alias);

    if (it != aliases.end())
        return it->second;
    else
        return NOT_EXIST_SCENE;
}

ID Dengine::getUniqueSceneId() {
    return nextSceneId++;
}