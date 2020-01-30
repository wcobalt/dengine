//
// Created by wcobalt on 1/29/20.
//

#include "XPlatformBuilder.h"
#include "Window/X/WindowManagerX.h"
#include "Window/WindowManager.h"
#include "Network/NetworkManager.h"
#include "Audio/AudioManager.h"
#include "Input/GamepadManager.h"
#include "../Exceptions/PlatformBuildException.h"
#include "Platform.h"

using namespace dengine;

void XPlatformBuilder::initializeWindowManager(int x, int y, uint width, uint height, std::string title) {
    windowManager = std::make_unique<WindowManagerX>(x, y, width, height, std::move(title));
}

void XPlatformBuilder::initializeNetworkManager() {
    networkManager = std::make_unique<NetworkManager>();
}

void XPlatformBuilder::initializeAudioManager() {
    audioManager = std::make_unique<AudioManager>();
}

void XPlatformBuilder::initializeGamepadManager() {
    gamepadManager = std::make_unique<GamepadManager>();
}

void XPlatformBuilder::clear() {
    windowManager = nullptr;
    networkManager = nullptr;
    audioManager = nullptr;
    gamepadManager = nullptr;
}

std::unique_ptr<Platform> XPlatformBuilder::build() const {
    if (windowManager == nullptr)
        throw PlatformBuildException("Window Manager is not initialized");

    if (networkManager == nullptr)
        throw PlatformBuildException("Network Manager is not initialized");

    if (audioManager == nullptr)
        throw PlatformBuildException("Audio Manager is not initialized");

    if (gamepadManager == nullptr)
        throw PlatformBuildException("Gamepad Manager is not initialized");

    return std::make_unique<Platform>(std::move(windowManager), std::move(networkManager),
              std::move(audioManager), std::move(gamepadManager));
}
