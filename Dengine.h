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

    using std::vector;
    using std::shared_ptr;

    typedef ulong ID;

    class Dengine {
    private:
        float fps;

        shared_ptr<WindowManager> windowManager;

        vector<shared_ptr<Entry<Scene>>> scenes;

        bool mIsPaused;
        bool isGameStopped;

        ID currentScene;

        ID nextAddedSceneId;

        void update();
        ID getUniqueSceneId();
    public:
        Dengine(shared_ptr<WindowManager> windowManager);

        void setFPS(float fps);
        float getFPS() const;

        shared_ptr<WindowManager> getWindowManager() const;

        void run();
        void pause();
        void stop();
        bool isPaused() const;

        ID addScene(shared_ptr<Scene> scene);
        void removeScene(ID id);
        void loadScene(ID id);
        ID getCurrentScene() const;

        shared_ptr<Scene> getScene(ID id) const;
    };
}

#endif //DENGINE_DENGINE_H
