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

void Dengine::setWindowPosition(int x, int y) {

}

void Dengine::setWindowSize(unsigned int window, unsigned int height) {

}

void Dengine::setWindowTitle(std::string title) {

}

void Dengine::start() {

}