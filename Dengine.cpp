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

    if(!data->isWindowClosing()) {
        MousePosition mousePosition = data->getMousePosition();

        p("Is windowed: ");
        p(data->isWindowWindowed() ? "true" : "false");
        p("\n");//
        p("Is maximized: ");
        p(data->isWindowMaximized() ? "true" : "false");
        p("\n");//
        p("Is minimzed: ");
        p(data->isWindowMinimized() ? "true" : "false");
        p("\n");//
        p("Is resized: ");
        p(data->isWindowResized() ? "true" : "false");
        p("\n");//
        p("Got focus: ");
        p(data->windowGotFocus() ? "true" : "false");
        p("\n");
        p("Lost focus: ");
        p(data->windowLostFocus() ? "true" : "false");
        p("\n");
        p("Scroll direction: ");
        std::printf("%d", data->getMouseWheelDirection());
        p("\n");//
        p("Mouse Position: ");
        std::printf("%d", mousePosition.getRootMouseX());
        p(" ");//
        std::printf("%d", mousePosition.getRootMouseY());
        p(" ");//
        std::printf("%d", mousePosition.getWindowMouseX());
        p(" ");//
        std::printf("%d", mousePosition.getWindowMouseY());
        p("\n");//

        std::set<int> pk, rk, pb, rb;

        pk = data->getPressedKeys();
        rk = data->getReleasedKeys();
        pb = data->getPressedButtons();
        rb = data->getReleasedButtons();
        //focus
        p("Pressed keys: ");
        for (int key : pk) {
            printf("%d", key);
            p(" ");//
        }
        p("\n");

        p("Released keys: ");
        for (int key : rk) {
            printf("%d", key);
            p(" ");//
        }
        p("\n");

        p("Pressed buttons: ");
        for (int key : pb) {
            printf("%d", key);
            p(" ");//
        }
        p("\n");

        p("Released buttons: ");//
        for (int key : rb) {
            printf("%d", key);
            p(" ");
        }
        p("\n");

        p("--------------------------------------------");
    } else exit(200);

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