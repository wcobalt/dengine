//
// Created by wcobalt on 16.09.18.
//

#include <future>
#include <thread>
#include <chrono>
#include <memory>

#include "Dengine.h"
#include "DengineAccessor.h"
#include "Window/WindowManager.h"
#include "ScenesManager.h"
#include "Exceptions/DengineIsNotInitializedException.h"

using std::shared_ptr;
using namespace dengine;
using namespace dengine::platform::window;
using namespace dengine::exceptions;

Dengine::Dengine(shared_ptr<WindowManager> windowManager):mIsPaused(0), isGameStopped(0) {
    setWindowManager(windowManager);

    scenesManager = std::make_shared<ScenesManager>();
}

void Dengine::init(shared_ptr<WindowManager> windowManager) {
    if (!dengine) {
        Dengine* dengine = new Dengine(windowManager);

        shared_ptr<Dengine> fake(dengine);

        Dengine::dengine = fake;
    }
}

void Dengine::update() {
    windowManager->checkEvents();
    scenesManager->update({});
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