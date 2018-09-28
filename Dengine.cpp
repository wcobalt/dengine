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

Dengine::Dengine() = default;

Dengine::Dengine(int windowX, int windowY, unsigned int windowWidth,
                 unsigned int windowHeight, std::string windowTitle,
                 WindowManager* windowManager) {

    this->windowManager = windowManager;
    //@todo add parameters' names in header-files

    //@todo windowTitle copies creating!!!
    windowManager->getWindowAccessor()->initialize(windowX, windowY, windowWidth,
                                                   windowHeight, windowTitle);

    isPaused = false;
}

void Dengine::update() {
    EventsData* data = windowManager->getWindowAccessor()->checkEvents();

    delete data;
}

void Dengine::p(const char* str) {
    std::cout << str;
};

int Dengine::getFPS() {
    return fps;
}

void Dengine::setFPS(int fps) {
    this->fps = fps;
}

WindowManager* Dengine::getWindowManager() {
    //@todo is it okay, return object not pointer to it?
    return windowManager;
}

void Dengine::setAllPaused(bool isPaused) {
    this->isPaused = isPaused;
}

bool Dengine::isAllPaused() {
    return isPaused;
}

void Dengine::start() {
    while(!isPaused) {
        std::async(&Dengine::update, this);

        //@todo async may take some time real_fps != fps
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}