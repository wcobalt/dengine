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

Dengine::Dengine(std::shared_ptr<WindowManager> windowManager) {
    this->windowManager = windowManager;

    mIsPaused = false;
    isGameStopped = false;
    lastAddedSceneId = 1;
}

void Dengine::update() {
    std::shared_ptr<const EventsData> data = windowManager->getWindowAccessor()->checkEvents();
}

float Dengine::getFPS() const {
    return fps;
}

void Dengine::setFPS(float fps) {
    this->fps = fps;
}

std::shared_ptr<WindowManager> Dengine::getWindowManager() const {
    return windowManager;
}

void Dengine::run() {
    isGameStopped = false;

    while (!isGameStopped) {
        std::future fut = std::async(&Dengine::update, *this);

        //@todo async may take some time real_fps != fps
        std::this_thread::sleep_for(std::chrono::milliseconds((int) (1000.0 / fps)));
    }
}

void Dengine::pause() {
    mIsPaused = true;
}

void Dengine::stop() {
    isGameStopped = true;
}

bool Dengine::isPaused() const {
    return mIsPaused;
}

ulong Dengine::getUniqueSceneId() {
    return lastAddedSceneId++;
}

ulong Dengine::addScene(std::shared_ptr<Scene> scene) {
    std::shared_ptr<Entry<Scene>> newScene;

    ulong id = getUniqueSceneId();

    newScene = std::make_shared<Entry<Scene>>(new Entry<Scene>(scene, id));

    scenes.push_back(newScene);

    return id;
}
//@todo do add string scene ids?
//@todo exceptions

void Dengine::loadScene(ulong id) {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if (it->get()->getId() == id) {
            currentScene = id;

            //
            return;
        }

    throw NoSuitableSceneException();
}

void Dengine::removeScene(ulong id) {
    if (id != currentScene) {
        for (auto it = scenes.begin(); it != scenes.end(); it++)
            if (it->get()->getId() == id) {

                //

                return;
            }

        throw NoSuitableSceneException();
    }

    throw CurrentSceneRemovingException();
}

std::shared_ptr<Scene> Dengine::getScene(ulong id) const {
    for (auto it = scenes.begin(); it != scenes.end(); it++)
        if (it->get()->getId() == id)
            return it->get()->getObject();

    throw NoSuitableSceneException();
}

ulong Dengine::getCurrentScene() const {
    if (currentScene != 0)
        return currentScene;

    throw NoCurrentSceneException();
}