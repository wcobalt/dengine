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
    class Platform {
    private:
        std::unique_ptr<WindowManager> windowManager;
        std::unique_ptr<NetworkManager> networkManager;
        std::unique_ptr<AudioManager> audioManager;
        std::unique_ptr<GamepadManager> gamepadManager;
    public:
        Platform(std::unique_ptr<WindowManager> windowManager, std::unique_ptr<NetworkManager> networkManager,
                std::unique_ptr<AudioManager> audioManager, std::unique_ptr<GamepadManager> gamepadManager);
        
        WindowManager & getWindowManager();

        NetworkManager & getNetworkManager();

        AudioManager & getAudioManager();

        GamepadManager & getGamepadManager();
    };
}

#endif //DENGINE_PLATFORMSET_H
