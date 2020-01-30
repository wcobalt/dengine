//
// Created by wcobalt on 16.09.18.
//

#include <future>
#include <thread>
#include <chrono>
#include <memory>

#include "Dengine.h"
#include "Platform/Window/WindowManager.h"
#include "ScenesManager.h"
#include "Scene.h"
#include "Exceptions/DengineException.h"
#include "Platform/Platform.h"

using namespace dengine;

const char Dengine::VERSION_STRING[] = "0.2.0:0";

Dengine::Dengine(std::unique_ptr<Platform> platformSet, float fps) : mIsIgnoringInactive(false), isGameStopped(false),
            fps(fps), platformSet(std::move(platformSet)), scenesManager(std::make_unique<ScenesManager>()) {}

void Dengine::init(std::unique_ptr<Platform> platformSet) {
    init(std::move(platformSet), DEFAULT_FPS);
}

void Dengine::init(std::unique_ptr<Platform> platformSet, float fps) {
    class for_make_unique : public Dengine {
    public:
        for_make_unique(std::unique_ptr<Platform> platformSet, float fps) : Dengine(std::move(platformSet), fps) {}
    };

    if (!dengine) {
        Dengine::dengine = std::make_unique<for_make_unique>(std::move(platformSet), fps);
    }
}

Dengine & Dengine::get() {
    if (!dengine)
        return *dengine;

    throw DengineException("Dengine is not initialized. Call init()");
}

void Dengine::setFps(float fps) {
    this->fps = fps;
}

float Dengine::getFps() const {
    return getRealFps() < fps ? getRealFps() : fps;
}

float Dengine::getRealFps() const {
    return static_cast<float>(10e9 / deltaTime);
}

float Dengine::getDeltaTime() const {
    return deltaTime;
}

void Dengine::update() {
    eventsState = std::move(platformSet->getWindowManager()->getEventsState());

    scenesManager->handleExternalEvent(ScenesManager::EventType::UPDATE);
}

void Dengine::run() {
    if (fps == 0) throw DengineException("Fps cannot be zero. Use setFps()");

    while (!isGameStopped) {
        auto start = std::chrono::high_resolution_clock::now();

        update();

        auto finish = std::chrono::high_resolution_clock::now();

        if (isGameStopped) scenesManager->handleExternalEvent(ScenesManager::EventType::GAME_END);

        deltaTime = (finish - start).count();
        float supposedFrameTime = static_cast<float>(10e9 / fps);
        float awaitTime = supposedFrameTime - deltaTime;

        if (awaitTime > 0)
            std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<long>(awaitTime)));
    }

    //stop must be called from within the loop, so if the loop is broken then stop was called for sure (almost)
    platformSet->getWindowManager()->destroy();
}

void Dengine::stop() {
    isGameStopped = true;
}

std::string Dengine::toString() const {
    auto& scene = scenesManager->getCurrentScene();
    const std::string& alias = scene.getAlias();

    return "Dengine (v" + std::string(VERSION_STRING) + "):\n" +
           "Current scene: " + std::to_string(scene.getId()) + " (" + (alias.empty() ? "<no alias>" : alias) + ")";
}

ScenesManager & Dengine::getScenesManager() const {
    return *scenesManager;
}

Platform & Dengine::getPlatform() const {
    return *platformSet;
}

const Events & Dengine::getEventsState() {
    return *eventsState;
}
