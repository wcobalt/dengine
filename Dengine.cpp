//
// Created by wcobalt on 16.09.18.
//

#include <GL/glx.h>
#include <GL/gl.h>
#include <future>
#include <thread>
#include <chrono>
#include <iostream>

#include "Dengine.h"
#include "Exceptions/DengineIsNotInitializedException.h"

using namespace dengine;
using namespace dengine::exceptions;

Dengine::Dengine(shared_ptr<WindowManager> windowManager) {
    setWindowManager(windowManager);

    mIsPaused = false;
    isGameStopped = false;

    scenesManager = std::make_shared<ScenesManager>(new ScenesManager());
}

void Dengine::init(shared_ptr<WindowManager> windowManager) {
    if (!dengine)
        dengine = std::make_shared<Dengine>(new Dengine(windowManager));
}

void Dengine::update() {
    windowManager->checkEvents();
    scenesManager->update();
}

void Dengine::setFPS(float fps) {
    this->fps = fps;
}

void Dengine::setWindowManager(shared_ptr<WindowManager> windowManager) {
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

shared_ptr<WindowManager> Dengine::getWindowManager() const {
    return windowManager;
}

float Dengine::getFPS() const {
    return fps;
}

bool Dengine::isPaused() const {
    return mIsPaused;
}

shared_ptr<ScenesManager> Dengine::getScenesManager() const {
    return scenesManager;
}

shared_ptr<Dengine> Dengine::get() {
    if (!dengine)
        return dengine;

    throw DengineIsNotInitializedException();
}