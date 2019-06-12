//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_WINDOWSTATE_H
#define DENGINE_WINDOWSTATE_H

#include "../../DObject.h"

namespace dengine::events::window {
    class WindowState : DObject {
    public:
        virtual bool isWindowMaximized() const = 0;

        virtual bool isWindowMinimized() const = 0;

        virtual bool isWindowWindowed() const = 0;

        virtual bool isWindowResized() const = 0;

        virtual bool gotFocus() const = 0;

        virtual bool lostFocus() const = 0;

        virtual bool isWindowClosing() const = 0;
    };
}

#endif //DENGINE_WINDOWSTATE_H
