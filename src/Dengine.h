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
    class PlatformSet;
    class EventsState;
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

        std::shared_ptr<PlatformSet> platformSet;
        std::shared_ptr<ScenesManager> scenesManager;

        bool mIsIgnoringInactive;
        bool isGameStopped;

        static std::shared_ptr<Dengine> dengine;

        std::shared_ptr<EventsState> eventsState;

        void update();

        Dengine(std::shared_ptr<PlatformSet> platformSet, float fps);
    public:
        static const char VERSION_STRING[];

        static constexpr unsigned VERSION_MAJOR = 0;
        static constexpr unsigned VERSION_MINOR = 2;
        static constexpr unsigned VERSION_INDEX = 0;
        static constexpr unsigned VERSION_BUILD = 0;

        //SOLID
        static void init(std::shared_ptr<PlatformSet> platformSet);

        static void init(std::shared_ptr<PlatformSet> platformSet, float fps);

        static std::shared_ptr<Dengine> get();

        void setFps(float fps);

        float getFps() const;

        float getRealFps() const;

        float getDeltaTime() const;

        void setIgnoreInactive(bool doIgnoreInactive);

        bool isIgnoringInactive() const;

        void run();

        void stop();

        std::string toString() const;

        std::shared_ptr<EventsState> getEventsState();

        std::shared_ptr<ScenesManager> getScenesManager() const;

        std::shared_ptr<PlatformSet> getPlatformSet() const;
    };
}

#endif //DENGINE_DENGINE_H
