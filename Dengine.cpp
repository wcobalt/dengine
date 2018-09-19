//
// Created by wcobalt on 16.09.18.
//

#include "Dengine.h"
#include "Steam.h"
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>

Dengine::Dengine() = default;

Dengine::Dengine(int windowX, int windowY, unsigned int windowWidth,
                 unsigned int windowHeight, std::string windowTitle) {
    //@todo add parameters' names in header-files
    GLint attributes[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24, None};

    long eventsMask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
                      Button1MotionMask | Button2MotionMask | Button3MotionMask |
                      Button4MotionMask | Button5MotionMask | ButtonMotionMask;

    //@todo windowTitle copies creating!!!
    windowManager->getWindowAccessor()->initialize(windowX, windowY, windowWidth, windowHeight,
                                                   attributes, eventsMask, windowTitle);

    steam = new Steam(this);

    while(!isPaused) {
        std::async(steam->update);
    }
}

int Dengine::getFPS() {
    return fps;
}

void Dengine::setFPS(int fps) {
    this->fps = fps;
}

void Dengine::setWindowManager(WindowManager* windowManager) {
    this->windowManager = windowManager;
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


}