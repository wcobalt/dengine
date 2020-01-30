//
// Created by wcobalt on 1/29/20.
//

#include "Platform.h"
#include "Window/WindowManager.h"
#include "Audio/AudioManager.h"
#include "Input/GamepadManager.h"
#include "Network/NetworkManager.h"

using namespace dengine;

Platform::Platform(std::unique_ptr<WindowManager> windowManager, std::unique_ptr<NetworkManager> networkManager,
                   std::unique_ptr<AudioManager> audioManager, std::unique_ptr<GamepadManager> gamepadManager) :
                   windowManager(std::move(windowManager)), networkManager(std::move(networkManager)),
                   audioManager(std::move(audioManager)), gamepadManager(std::move(gamepadManager)) {}

WindowManager & Platform::getWindowManager() {
    return *windowManager;
}

NetworkManager & Platform::getNetworkManager() {
    return *networkManager;
}

AudioManager & Platform::getAudioManager() {
    return *audioManager;
}

GamepadManager & Platform::getGamepadManager() {
    return *gamepadManager;
}
