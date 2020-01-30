//
// Created by wcobalt on 11/17/19.
//

#include "Events.h"

using namespace dengine;

Events::Events(std::unique_ptr<WindowState> windowState, std::unique_ptr<KeyboardState> keyboardState,
               std::unique_ptr<MouseState> mouseState) : windowState(std::move(windowState)),
                                                                   keyboardState(std::move(keyboardState)),
                                                                   mouseState(std::move(mouseState)) {}

const WindowState & Events::getWindowState() const {
    return *windowState;
}

const KeyboardState & Events::getKeyboardState() const {
    return *keyboardState;
}

const MouseState & Events::getMouseState() const {
    return *mouseState;
}
