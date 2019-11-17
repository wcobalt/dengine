//
// Created by wcobalt on 11/17/19.
//

#include "EventsState.h"

using namespace dengine;

EventsState::EventsState(std::shared_ptr<WindowState> windowState, std::shared_ptr<KeyboardState> keyboardState,
                         std::shared_ptr<MouseState> mouseState) : windowState(windowState),
                         keyboardState(keyboardState), mouseState(mouseState) {}

std::shared_ptr<WindowState> EventsState::getWindowState() const {
    return windowState;
}

std::shared_ptr<KeyboardState> EventsState::getKeyboardState() const {
    return keyboardState;
}

std::shared_ptr<MouseState> EventsState::getMouseState() const {
    return mouseState;
}
