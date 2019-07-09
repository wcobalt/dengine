//
// Created by wcobalt on 7/9/19.
//
#include <memory>

#include "DefaultWindowStateBuilder.h"
#include "DefaultWindowState.h"

using namespace dengine::events::window;

void DefaultWindowStateBuilder::setMaximized(bool wasMaximized) {
    mWasMaximized = wasMaximized;
}

void DefaultWindowStateBuilder::setWindowed(bool wasWindowed) {
    mWasWindowed = wasWindowed;
}

void DefaultWindowStateBuilder::setIconified(bool wasIconified) {
    mWasIconified = wasIconified;
}

void DefaultWindowStateBuilder::setResized(bool wasResized) {
    mWasResized = wasResized;
}

void DefaultWindowStateBuilder::setGotFocus(bool gotFocus) {
    mGotFocus = gotFocus;
}

void DefaultWindowStateBuilder::setLostFocus(bool lostFocus) {
    mLostFocus = lostFocus;
}

void DefaultWindowStateBuilder::setClosing(bool isClosing) {
    mIsClosing = isClosing;
}

std::shared_ptr<WindowState> DefaultWindowStateBuilder::build() const {
    std::shared_ptr<WindowState> result(new DefaultWindowState(mWasMaximized, mWasWindowed, mWasIconified,
                                            mWasResized, mGotFocus, mLostFocus, mIsClosing));

    return result;
}