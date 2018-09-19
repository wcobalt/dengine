#include <string>
#include "WindowAccessors/WindowManager.h"
#include "Steam.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H


class Dengine {
private:
    int fps;
    WindowManager* windowManager;
    bool isPaused;
    Steam* steam;
public:
    Dengine();
    Dengine(int windowX, int windowY, unsigned int windowWidth,
                     unsigned int windowHeight, std::string windowTitle);
    //@todo to Window class
    //@todo getXXX() add
    void setFPS(int fps);
    int getFPS();
    void setWindowManager(WindowManager* windowManager);
    WindowManager* getWindowManager();
    void start();
    void setAllPaused(bool isPaused);
    bool isAllPaused();
};


#endif //DENGINE_DENGINE_H
