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

namespace dengine {
    using namespace windowaccessors;

    class Dengine {
    private:
        float fps;
        std::shared_ptr<WindowManager> windowManager;
        bool mIsPaused;
        std::vector<std::shared_ptr<Scene>> scenes;
        ulong currentScene;
    public:
        Dengine(std::shared_ptr<WindowManager> windowManager);

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

        void loadScene(const std::string &id);

        std::shared_ptr<Scene> getCurrentScene() const;
    };
}

#endif //DENGINE_DENGINE_H
