//
// Created by wcobalt on 7/9/19.
//
#include <memory>

#include "DefaultWindowStateBuilder.h"
#include "DefaultWindowState.h"

using namespace dengine;

void DefaultWindowStateBuilder::setMaximized(bool wasMaximized) {
    this->wasMaximized = wasMaximized;
}

void DefaultWindowStateBuilder::setWindowed(bool wasWindowed) {
    this->wasWindowed = wasWindowed;
}

void DefaultWindowStateBuilder::setIconified(bool wasIconified) {
    this->wasIconified = wasIconified;
}

void DefaultWindowStateBuilder::setResized(bool wasResized) {
    this->wasResized = wasResized;
}

void DefaultWindowStateBuilder::setGotFocus(bool gotFocus) {
    this->gotFocus = gotFocus;
}

void DefaultWindowStateBuilder::setLostFocus(bool lostFocus) {
    this->lostFocus = lostFocus;
}

void DefaultWindowStateBuilder::setClosing(bool isClosing) {
    this->isClosing = isClosing;
}

std::shared_ptr<WindowState> DefaultWindowStateBuilder::build() const {
    std::shared_ptr<WindowState> result(new DefaultWindowState(wasMaximized, wasWindowed, wasIconified,
                                            wasResized, gotFocus, lostFocus, isClosing, wasMoved));

    return result;
}

void DefaultWindowStateBuilder::setMoved(bool wasMoved) {
    this->wasMoved = wasMoved;
}
