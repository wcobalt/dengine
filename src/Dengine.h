//
// Created by wcobalt on 16.09.18.
//
#include <string>
#include <memory>

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H

namespace dengine {
    class ScenesManager;

    namespace window {
        class WindowManager;
    }
}

#include "Coreutils/ID.h"
#include "DObject.h"

/* Core release features for implementation:
 * only one dengine namespace
 * optimize by assignments, init list and other
 * Image class
 * implement windowaccessor
 * keyboard, window state (with builders)
 * review run/pause/stop API
 * review Dengine->ScenesManager->Scene->GameObject->Component API (Core API)
 */

namespace dengine {
    //singleton
    class Dengine : public DObject {
    public:
        static const dengine::coreutils::ID MINIMAL_SAFE_ID = 3;
    private:
        float fps;

        std::shared_ptr<window::WindowManager> windowManager;
        std::shared_ptr<ScenesManager> scenesManager;

        bool mIsPaused;
        bool isGameStopped;

        static std::shared_ptr<dengine::Dengine> dengine;

        void update();
        void run();

        Dengine(std::shared_ptr<window::WindowManager> windowManager);
    public:
        //SOLID
        static void init(std::shared_ptr<window::WindowManager> windowManager);

        void setFPS(float fps);

        void setWindowManager(std::shared_ptr<window::WindowManager> windowManager);

        void setPaused(bool isPaused);
        void stop();

        float getFPS() const;

        std::shared_ptr<window::WindowManager> getWindowManager() const;

        bool isPaused() const;

        std::shared_ptr<ScenesManager> getScenesManager() const;

        static std::shared_ptr<dengine::Dengine> get();
    };
}

#endif //DENGINE_DENGINE_H
