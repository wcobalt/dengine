//
// Created by wcobalt on 16.09.18.
//
#include <string>
#include <memory>

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H

namespace dengine {
    class ScenesManager;
    class WindowManager;
}

#include "Coreutils/ID.h"
#include "DObject.h"

/* "Core" release features for implementation:
 * 2) optimize by assignments, init list and other, exceptions reduce
 * 3) clear methods for builders
 * 4) virtual inheritance of interfaces
 * 5) review run/pause/stop API
 * 6) review Dengine->ScenesManager->Scene->GameObject->Component API (Core API)
 */

namespace dengine {
    //singleton
    class Dengine : public DObject {
    public:
        static const dengine::ID MINIMAL_SAFE_ID = 3;
    private:
        float fps;

        std::shared_ptr<WindowManager> windowManager;
        std::shared_ptr<ScenesManager> scenesManager;

        bool mIsPaused;
        bool isGameStopped;

        static std::shared_ptr<Dengine> dengine;

        void update();
        void run();

        Dengine(std::shared_ptr<WindowManager> windowManager);
    public:
        //SOLID
        static void init(std::shared_ptr<WindowManager> windowManager);

        void setFPS(float fps);

        void setWindowManager(std::shared_ptr<WindowManager> windowManager);

        void setPaused(bool isPaused);
        void stop();

        float getFPS() const;

        std::shared_ptr<WindowManager> getWindowManager() const;

        bool isPaused() const;

        std::shared_ptr<ScenesManager> getScenesManager() const;

        static std::shared_ptr<Dengine> get();
    };
}

#endif //DENGINE_DENGINE_H
