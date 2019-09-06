//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_DEFAULTWINDOWSTATE_H
#define DENGINE_DEFAULTWINDOWSTATE_H

#include "WindowState.h"

namespace dengine {
    class DefaultWindowState : public WindowState {
    private:
        bool mWasMaximized, mWasIconified,
                mWasWindowed, mWasResized,
                mGotFocus, mLostFocus,
                mIsClosing, mWasMoved;
    public:
        DefaultWindowState(bool wasMaximized, bool wasWindowed, bool wasIconified,
                           bool wasResized, bool gotFocus, bool lostFocus, bool isClosing,
                           bool wasMoved);

        bool wasMaximized() const;

        bool wasWindowed() const;

        bool wasIconified() const;

        bool wasResized() const;

        bool gotFocus() const;

        bool lostFocus() const;

        bool isClosing() const;

        bool wasMoved() const;
    };
}

#endif //DENGINE_DEFAULTWINDOWSTATE_H
