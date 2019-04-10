//
// Created by wcobalt on 16.09.18.
//
#include <string>
#include <memory>

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H

#include "WindowAccessors/WindowManager.h"
#include "Utils/String.h"
#include "Coreutils/Entry.h"
#include "ScenesManager.h"
#include "Coreutils/ID.h"
#include "DObject.h"
#include "Scene.h"

namespace dengine {
    using namespace windowaccessors;
    using namespace utils;
    using namespace events;
    using namespace coreutils;

    //singleton
    class Dengine : public DObject {
    public:
        static const ID MINIMAL_SAFE_ID = 3;
    private:
        float fps;

        shared_ptr<WindowManager> windowManager;
        shared_ptr<ScenesManager> scenesManager;

        bool mIsPaused;
        bool isGameStopped;

        static shared_ptr<Dengine> dengine;

        void update();
        void run();

        //@todo NetworkManager, AudioManager
        Dengine(shared_ptr<WindowManager> windowManager);
    public:
        //SOLID
        static void init(shared_ptr<WindowManager> windowManager);

        void setFPS(float fps);

        void setWindowManager(shared_ptr<WindowManager> windowManager);

        void setPaused(bool isPaused);
        void stop();

        float getFPS() const;

        shared_ptr<WindowManager> getWindowManager() const;

        bool isPaused() const;

        shared_ptr<ScenesManager> getScenesManager() const;

        static shared_ptr<Dengine> get();
    };
}

#endif //DENGINE_DENGINE_H
