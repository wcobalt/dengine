//
// Created by wcobalt on 16.09.18.
//

#include "Dengine.h"

Dengine::Dengine() = default;

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

void Dengine::start() {

}