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
#include "Coreutils/Entry.h"

namespace dengine {
    using namespace windowaccessors;
    using namespace coreutils;
    class Dengine {
    private:
        float fps;

        std::shared_ptr<WindowManager> windowManager;

        std::vector<std::shared_ptr<Entry<Scene>>> scenes;

        bool mIsPaused;
        bool isGameStopped;

        ulong currentScene;

        ulong lastAddedSceneId;

        void update();
        ulong getUniqueSceneId();
    public:
        Dengine(std::shared_ptr<WindowManager> windowManager);

        //@todo to Window class
        void setFPS(float fps);
        float getFPS() const;

        std::shared_ptr<WindowManager> getWindowManager() const;

        void run();
        void pause();
        void stop();
        bool isPaused() const;

        ulong addScene(std::shared_ptr<Scene> scene);
        void removeScene(ulong id);
        void loadScene(ulong id);
        ulong getCurrentScene() const;
        std::shared_ptr<Scene> getScene(ulong id) const;
    };
}

#endif //DENGINE_DENGINE_H
