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

Dengine::Dengine(int windowX, int windowY, unsigned int windowWidth,
                 unsigned int windowHeight, std::string windowTitle,
                 WindowManager& windowManager):windowManager(windowManager) {

    //this->windowManager = windowManager; (keeping for below comment)
    //@todo add parameters' names in header-files

    //@todo windowTitle copies creating!!!
    windowManager.getWindowAccessor().initialize(windowX, windowY, windowWidth,
                                                   windowHeight, windowTitle);

    mIsPaused = false;
}

void Dengine::update() {
    const EventsData& data = windowManager.getWindowAccessor().checkEvents();

    delete &data;
}

int Dengine::getFPS() const{
    return fps;
}

void Dengine::setFPS(int fps) {
    this->fps = fps;
}

WindowManager& Dengine::getWindowManager() const{
    return windowManager;
}

void Dengine::run() {
    while(!mIsPaused) {
        std::async(&Dengine::update, *this);

        //@todo async may take some time real_fps != fps
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}

void Dengine::pause() {
    mIsPaused = true;
}

bool Dengine::isPaused() const {
    return mIsPaused;
}

void Dengine::addScene(Scene& scene) {
    scenes.push_back(&scene);
}

void Dengine::loadScene(std::string id) {
    unsigned long count = scenes.size();

    for (unsigned long i = 0; i < count; i++) {
        if (scenes[i]->getID() == id) currentScene = scenes[i];
    }
}

Scene& Dengine::getLoadedScene() const{
    return *currentScene;
}