//
// Created by wcobalt on 1/29/20.
//
#include <memory>

#ifndef DENGINE_XPLATFORMBUILDER_H
#define DENGINE_XPLATFORMBUILDER_H

#include "PlatformBuilder.h"

namespace dengine {
    class WindowManager;
    class NetworkManager;
    class AudioManager;
    class GamepadManager;
}

//if WindowsPlatformBuilder looks exactly like that then exclude initializeX methods to PlatformBuilder and members
//and build and clear implementation too
namespace dengine {
    class XPlatformBuilder : public PlatformBuilder {
    private:
        std::unique_ptr<WindowManager> windowManager = nullptr;
        std::unique_ptr<NetworkManager> networkManager = nullptr;
        std::unique_ptr<AudioManager> audioManager = nullptr;
        std::unique_ptr<GamepadManager> gamepadManager = nullptr;
    public:
        void initializeWindowManager(int x, int y, uint width, uint height, std::string title);

        void initializeNetworkManager();

        void initializeAudioManager();

        void initializeGamepadManager();

        void clear() override;

        std::unique_ptr<Platform> build() const override;
    };
}

#endif //DENGINE_XPLATFORMBUILDER_H
