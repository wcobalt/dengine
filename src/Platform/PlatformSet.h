//
// Created by wcobalt on 5/29/19.
//

#include <memory>

#ifndef DENGINE_PLATFORMSET_H
#define DENGINE_PLATFORMSET_H

namespace dengine {
    class WindowManager;
    class NetworkManager;
    class AudioManager;
    class GamepadManager;
}

namespace dengine {
    class PlatformSet {
    public:
        virtual std::shared_ptr<WindowManager> getWindowManager() const = 0;

        virtual std::shared_ptr<NetworkManager> getNetworkManager() const = 0;

        virtual std::shared_ptr<AudioManager> getAudioManager() const = 0;

        virtual std::shared_ptr<GamepadManager> getGamepadManager() const = 0;
    };
}

#endif //DENGINE_PLATFORMSET_H
