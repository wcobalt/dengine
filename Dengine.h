
//#include "Scene.h"

//
// Created by wcobalt on 16.09.18.
//
#include <string>
#include <vector>

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H

#include "Scene.h"
#include "WindowAccessors/WindowManager.h"

class Dengine {
private:
    int fps;
    WindowManager& windowManager;
    bool mIsPaused;
    std::vector<Scene*> scenes;
    Scene* currentScene;
public:
    Dengine(int windowX, int windowY, unsigned int windowWidth,
                     unsigned int windowHeight, std::string windowTitle,
                     WindowManager& windowManager);
    //@todo to Window class
    //@todo getXXX() add
    void setFPS(int fps);
    int getFPS() const;
    WindowManager& getWindowManager() const;
    void run();
    void pause();
    bool isPaused() const;
    void update();
    void addScene(Scene& scene);
    void loadScene(std::string id);
    Scene& getLoadedScene() const;
};


#endif //DENGINE_DENGINE_H
