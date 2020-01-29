//
// Created by wcobalt on 1/29/20.
//
#include <memory>

#ifndef DENGINE_XPLATFORM_H
#define DENGINE_XPLATFORM_H

#include "Platform.h"

namespace dengine {
    class WindowManager;
    class NetworkManager;
    class AudioManager;
    class GamepadManager;
}

namespace dengine {
    class XPlatform : public Platform {
    public:
        XPlatform(int x, int y, uint width, uint height, const std::string& title);
    };
}

#endif //DENGINE_XPLATFORM_H
