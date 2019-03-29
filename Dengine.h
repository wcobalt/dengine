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
#include "Utils/String.h"
#include "Coreutils/Entry.h"

namespace dengine {
    using namespace windowaccessors;
    using namespace coreutils;
    using namespace utils;

    using std::vector;
    using std::map;
    using std::shared_ptr;

    typedef ulong ID;

    class Dengine {
    private:
        float fps;

        shared_ptr<WindowManager> windowManager;

        vector<shared_ptr<Entry<Scene>>> scenes;
        map<String, ID> aliases;

        bool mIsPaused;
        bool isGameStopped;

        ID currentScene;

        ID nextSceneId;

        void update();
        void run();
        ID getUniqueSceneId();
    public:
        const ID NOT_EXIST_SCENE = 0;

        Dengine(shared_ptr<WindowManager> windowManager);

        void setFPS(float fps);
        float getFPS() const;

        void setWindowManager(shared_ptr<WindowManager> windowManager);
        shared_ptr<WindowManager> getWindowManager() const;

        void setPaused(bool isPaused);
        void stop();
        bool isPaused() const;

        ID addScene(shared_ptr<Scene> scene);
        ID addScene(shared_ptr<Scene> scene, String alias);

        void removeScene(ID id);
        void removeScene(String alias);

        void loadScene(ID id);
        void loadScene(String alias);

        ID getCurrentScene() const;

        shared_ptr<Scene> getScene(ID id) const;
        shared_ptr<Scene> getScene(String alias) const;

        ID getIDByAlias(String alias) const;
    };
}

#endif //DENGINE_DENGINE_H
