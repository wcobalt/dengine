//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_DEFAULTWINDOWSTATE_H
#define DENGINE_DEFAULTWINDOWSTATE_H

#include "WindowState.h"

namespace dengine::events::window {
    class DefaultWindowState : WindowState {
    private:
        bool mWasMaximized, mWasIconified,
                mWasWindowed, mWasResized,
                mGotFocus, mLostFocus,
                mIsClosing;
    public:
        DefaultWindowState(bool wasMaximized, bool wasIconified, bool wasWindowed,
                           bool wasResized, bool gotFocus, bool lostFocus, bool isClosing);

        bool wasMaximized() const;

        bool wasWindowed() const;

        bool wasIconified() const;

        bool wasResized() const;

        bool gotFocus() const;

        bool lostFocus() const;

        bool isClosing() const;
    };
}

#endif //DENGINE_DEFAULTWINDOWSTATE_H
