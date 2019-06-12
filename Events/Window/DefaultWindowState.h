//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_DEFAULTWINDOWSTATE_H
#define DENGINE_DEFAULTWINDOWSTATE_H

#include "WindowState.h"

namespace dengine::events::window {
    class DefaultWindowState : WindowState {
    private:
        bool mIsWindowMaximized, mIsWindowMinimized,
                mIsWindowWindowed, mIsWindowResized,
                mGotFocus, mLostFocus,
                mIsWindowClosing;
    public:
        DefaultWindowState();

        DefaultWindowState(bool isWindowMaximized, bool isWindowMinimized, bool isWindowWindowed,
                           bool isWindowResized, bool gotFocus, bool lostFocus, bool isWindowClosing);

        bool isWindowMaximized() const;

        bool isWindowMinimized() const;

        bool isWindowWindowed() const;

        bool isWindowResized() const;

        bool gotFocus() const;

        bool lostFocus() const;

        bool isWindowClosing() const;
    };
}

#endif //DENGINE_DEFAULTWINDOWSTATE_H
