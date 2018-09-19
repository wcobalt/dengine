#include <string>
#include <vector>
#include "WindowAccessors/WindowManager.h"
//#include "Scene.h"

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
    //vector<Scene> scenes;
    int currentScene;
public:
    Dengine();
    Dengine(int windowX, int windowY, unsigned int windowWidth,
                     unsigned int windowHeight, std::string windowTitle,
                     WindowManager* windowManager);
    //@todo to Window class
    //@todo getXXX() add
    void setFPS(int fps);
    int getFPS();
    WindowManager* getWindowManager();
    void start();
    void setAllPaused(bool isPaused);
    bool isAllPaused();
    void update();
};


#endif //DENGINE_DENGINE_H
