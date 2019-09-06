//
// Created by wcobalt on 5/29/19.
//

#include <memory>

#ifndef DENGINE_PLATFORMSET_H
#define DENGINE_PLATFORMSET_H

namespace dengine {
    namespace window {
        class WindowManager;
    }

    namespace network {
        class NetworkManager;
    }

    namespace audio {
        class AudioManager;
    }

    namespace gamepad {
        class GamepadManager;
    }
}

namespace dengine {
    class PlatformSet {
    public:
        virtual std::shared_ptr<dengine::WindowManager> getWindowManager() const = 0;

        virtual std::shared_ptr<dengine::NetworkManager> getNetworkManager() const = 0;

        virtual std::shared_ptr<dengine::AudioManager> getAudioManager() const = 0;

        virtual std::shared_ptr<dengine::GamepadManager> getGamepadManager() const = 0;
    };
}

#endif //DENGINE_PLATFORMSET_H
