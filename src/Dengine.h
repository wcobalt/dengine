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
    class Platform;
    class Events;
}

#include "Coreutils/ID.h"
#include "DObject.h"

/* "Core" release features for implementation:
 * 2) optimize by assignments, init list and other
 * 3) clear methods for builders
 * 4) virtual inheritance of interfaces
 * 5) review run/pause/stop API
 * 6) review Dengine->ScenesManager->Scene->GameObject->Component API (Core API)
 */

namespace dengine {
    //singleton
    class Dengine : public DObject {
    private:
        float fps, deltaTime;

        std::unique_ptr<Platform> platformSet;
        std::unique_ptr<ScenesManager> scenesManager;

        bool mIsIgnoringInactive;
        bool isGameStopped;

        static std::unique_ptr<Dengine> dengine;

        std::unique_ptr<Events> eventsState;

        void update();

        Dengine(std::unique_ptr<Platform> platformSet, float fps);
    public:
        static const char VERSION_STRING[];

        static constexpr float DEFAULT_FPS = 30;

        static constexpr unsigned VERSION_MAJOR = 0;
        static constexpr unsigned VERSION_MINOR = 2;
        static constexpr unsigned VERSION_INDEX = 0;
        static constexpr unsigned VERSION_BUILD = 0;

        //SOLID
        static void init(std::unique_ptr<Platform> platformSet);

        static void init(std::unique_ptr<Platform> platformSet, float fps);

        static Dengine & get();

        void setFps(float fps);

        float getFps() const;

        float getRealFps() const;

        float getDeltaTime() const;

        void run();

        void stop();

        std::string toString() const;

        const Events & getEventsState();

        ScenesManager & getScenesManager() const;

        Platform & getPlatform() const;
    };
}

#endif //DENGINE_DENGINE_H
