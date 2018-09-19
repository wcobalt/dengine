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

Dengine::Dengine() = default;

Dengine::Dengine(int windowX, int windowY, unsigned int windowWidth,
                 unsigned int windowHeight, std::string windowTitle,
                 WindowManager* windowManager) {

    this->windowManager = windowManager;
    //@todo add parameters' names in header-files
    GLint attributes[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None};

    long eventsMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
                      Button1MotionMask | Button2MotionMask | Button3MotionMask |
                      Button4MotionMask | Button5MotionMask | ButtonMotionMask;

    //@todo windowTitle copies creating!!!
    windowManager->getWindowAccessor()->initialize(windowX, windowY, windowWidth, windowHeight,
                                                   attributes, eventsMask, windowTitle);

    isPaused = false;
}

void Dengine::update() {
    static int i;

    std::cout << ++i << "Duration\n";
}

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