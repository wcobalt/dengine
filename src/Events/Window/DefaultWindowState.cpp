//
// Created by wcobalt on 23.05.19.
//

#include "DefaultWindowState.h"

using namespace dengine;

DefaultWindowState::DefaultWindowState(bool wasMaximized, bool wasWindowed, bool wasIconified, bool wasResized,
                                       bool gotFocus, bool lostFocus, bool isClosing, bool wasMoved,
                                       bool wasHiddenToTray):
                                         mWasMaximized(wasMaximized), mWasWindowed(wasWindowed),
                                         mWasIconified(wasIconified), mWasResized(wasResized),
                                         mGotFocus(gotFocus), mLostFocus(lostFocus),
                                         mIsClosing(isClosing), mWasMoved(wasMoved),
                                         mWasHiddenToTray(wasHiddenToTray) {}

bool DefaultWindowState::wasMaximized() const {
    return mWasMaximized;
}

bool DefaultWindowState::wasWindowed() const {
    return mWasWindowed;
}

bool DefaultWindowState::wasIconified() const {
    return mWasIconified;
}

bool DefaultWindowState::wasResized() const {
    return mWasResized;
}

bool DefaultWindowState::gotFocus() const {
    return mGotFocus;
}

bool DefaultWindowState::lostFocus() const {
    return mLostFocus;
}

bool DefaultWindowState::isClosing() const {
    return mIsClosing;
}

bool DefaultWindowState::wasMoved() const {
    return mWasMoved;
}

bool DefaultWindowState::wasHiddenToTray() const {
    return mWasHiddenToTray;
}
