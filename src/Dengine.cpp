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
#include "Platform/PlatformSet.h"

using std::shared_ptr;
using namespace dengine;

const char Dengine::VERSION_STRING[] = "0.2.0:0";

Dengine::Dengine(shared_ptr<PlatformSet> platformSet, float fps) : mIsIgnoringInactive(false), isGameStopped(false), fps(fps) {
    this->platformSet = platformSet;

    scenesManager = std::make_shared<ScenesManager>();
}

void Dengine::init(shared_ptr<PlatformSet> platformSet) {
    init(platformSet, 0);
}

void Dengine::init(std::shared_ptr<PlatformSet> platformSet, float fps) {
    if (!dengine) {
        Dengine* dengine = new Dengine(platformSet, fps);

        shared_ptr<Dengine> fake(dengine);

        Dengine::dengine = fake;
    }
}

shared_ptr<Dengine> Dengine::get() {
    if (!dengine)
        return dengine;

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
    eventsState = platformSet->getWindowManager()->getEventsState();

    scenesManager->sendMessage(ScenesManagerMessage::UPDATE);
}

void Dengine::setIgnoreInactive(bool doIgnoreInactive) {
    mIsIgnoringInactive = doIgnoreInactive;
}

bool Dengine::isIgnoringInactive() const {
    return mIsIgnoringInactive;
}

void Dengine::run() {
    if (fps == 0) throw DengineException("Fps cannot be zero. Use setFps()");

    while (!isGameStopped) {
        auto start = std::chrono::high_resolution_clock::now();

        update();

        auto finish = std::chrono::high_resolution_clock::now();

        if (isGameStopped) scenesManager->sendMessage(ScenesManagerMessage::GAME_END);

        deltaTime = (finish - start).count();
        float supposedFrameTime = static_cast<float>(10e9 / fps);
        float awaitTime = supposedFrameTime - deltaTime;

        if (awaitTime > 0)
            std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<long>(awaitTime)));
    }

    //stop must be called from within the loop, so if loop is broken then stop was called for sure (almost)
    platformSet->getWindowManager()->destroy();
}

void Dengine::stop() {
    isGameStopped = true;
}

std::string Dengine::toString() const {
    auto scene = scenesManager->getCurrentScene();
    const std::string& alias = scene->getAlias();

    return "Dengine (v" + std::string(VERSION_STRING) + "):\n" +
            "Current scene: " + std::to_string(scene->getId()) + " (" + (alias.empty() ? "<no alias>" : alias) + ")\n"
            "Credits: \n" +
            "Author: Wert Cobalt (Artyom Drapun) <cobalt.itech@gmail.com>\n";
}

shared_ptr<ScenesManager> Dengine::getScenesManager() const {
    return scenesManager;
}

std::shared_ptr<PlatformSet> Dengine::getPlatformSet() const {
    return platformSet;
}

std::shared_ptr<EventsState> Dengine::getEventsState() {
    return eventsState;
}
