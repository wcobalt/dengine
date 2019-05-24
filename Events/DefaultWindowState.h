//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_DEFAULTWINDOWSTATE_H
#define DENGINE_DEFAULTWINDOWSTATE_H

#include "WindowState.h"

namespace dengine::events {
    class DefaultWindowState : WindowState {
    private:
        bool mIsWindowMaximized, mIsWindowMinimized,
                mIsWindowWindowed, mIsWindowResized,
                mIsWindowFocused, mIsWindowClosing;
    public:
        DefaultWindowState();

        DefaultWindowState(bool isWindowMaximized, bool isWindowMinimized, bool isWindowWindowed,
                           bool isWindowResized, bool isWindowFocused, bool isWindowClosing);

        bool isWindowMaximized() const;

        bool isWindowMinimized() const;

        bool isWindowWindowed() const;

        bool isWindowResized() const;

        bool isWindowFocused() const;

        bool isWindowClosing() const;
    };
}

#endif //DENGINE_DEFAULTWINDOWSTATE_H
