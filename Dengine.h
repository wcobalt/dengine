//
// Created by wcobalt on 16.09.18.
//
#include <string>
#include <vector>
#include <memory>

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H

#include "Scene.h"
#include "WindowAccessors/WindowManager.h"

class Dengine {
private:
    float fps;
    std::shared_ptr<WindowManager> windowManager;
    bool mIsPaused;
    std::vector<std::shared_ptr<Scene>> scenes;
    ulong currentScene;
public:
    Dengine(int windowX, int windowY, uint windowWidth,
                     uint windowHeight, std::string& windowTitle,
                     std::shared_ptr<WindowManager> windowManager);
    //@todo to Window class
    //@todo getXXX() add
    void setFPS(float fps);
    float getFPS() const;
    std::shared_ptr<WindowManager> getWindowManager() const;
    void run();
    void pause();
    bool isPaused() const;
    void update();
    void addScene(std::shared_ptr<Scene> scene);
    void loadScene(std::string& id);
    std::shared_ptr<Scene> getCurrentScene() const;
};


#endif //DENGINE_DENGINE_H
