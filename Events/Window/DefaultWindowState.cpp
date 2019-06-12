//
// Created by wcobalt on 23.05.19.
//

#include "DefaultWindowState.h"

using namespace dengine::events::window;

DefaultWindowState::DefaultWindowState():mIsWindowMaximized(0), mIsWindowMinimized(0),
                                         mIsWindowWindowed(0), mIsWindowResized(0),
                                         mGotFocus(0), mLostFocus(0),
                                         mIsWindowClosing(0) {}

DefaultWindowState::DefaultWindowState(bool isWindowMaximized, bool isWindowMinimized, bool isWindowWindowed,
                                       bool isWindowResized, bool gotFocus, bool lostFocus, bool isWindowClosing):
                                         mIsWindowMaximized(isWindowMaximized), mIsWindowMinimized(isWindowMinimized),
                                         mIsWindowWindowed(isWindowWindowed), mIsWindowResized(isWindowResized),
                                         mGotFocus(gotFocus), mLostFocus(lostFocus),
                                         mIsWindowClosing(isWindowClosing) {}

bool DefaultWindowState::isWindowMaximized() const {
    return mIsWindowMaximized;
}

bool DefaultWindowState::isWindowMinimized() const {
    return mIsWindowMinimized;
}

bool DefaultWindowState::isWindowWindowed() const {
    return mIsWindowWindowed;
}

bool DefaultWindowState::isWindowResized() const {
    return mIsWindowResized;
}

bool DefaultWindowState::gotFocus() const {
    return mGotFocus;
}

bool DefaultWindowState::lostFocus() const {
    return mLostFocus;
}

bool DefaultWindowState::isWindowClosing() const {
    return mIsWindowClosing;
}