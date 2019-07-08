//
// Created by wcobalt on 23.05.19.
//

#include "DefaultWindowState.h"

using namespace dengine::events::window;

DefaultWindowState::DefaultWindowState():mWasMaximized(false), mWasIconified(false),
                                         mWasWindowed(false), mWasResized(false),
                                         mGotFocus(false), mLostFocus(false),
                                         mIsClosing(false) {}

DefaultWindowState::DefaultWindowState(bool wasMaximized, bool wasIconified, bool wasWindowed,
                                       bool wasResized, bool gotFocus, bool lostFocus, bool isClosing):
                                         mWasMaximized(wasMaximized), mWasIconified(wasIconified),
                                         mWasWindowed(wasWindowed), mWasResized(wasResized),
                                         mGotFocus(gotFocus), mLostFocus(lostFocus),
                                         mIsClosing(isClosing) {}

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