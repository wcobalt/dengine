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

using namespace dengine;

Dengine::Dengine(std::shared_ptr<WindowManager> windowManager) {
    this->windowManager = windowManager;

    mIsPaused = false;
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
    while (!mIsPaused) {
        std::future fut = std::async(&Dengine::update, *this);

        //@todo async may take some time real_fps != fps
        std::this_thread::sleep_for(std::chrono::milliseconds((int) (1000.0 / fps)));
    }
}

void Dengine::pause() {
    mIsPaused = true;
}

bool Dengine::isPaused() const {
    return mIsPaused;
}

void Dengine::addScene(std::shared_ptr<Scene> scene) {
    scenes.push_back(scene);
}

void Dengine::loadScene(const std::string &id) {
    ulong count = scenes.size();

    for (ulong i = 0; i < count; i++) {
        if (scenes[i]->getID() == id) currentScene = i;
    }
}

std::shared_ptr<Scene> Dengine::getCurrentScene() const {
    return scenes[currentScene];
}