//
// Created by wcobalt on 11/17/19.
//
#include <memory>

#ifndef DENGINE_EVENTSSTATE_H
#define DENGINE_EVENTSSTATE_H

namespace dengine {
    class MouseState;
    class WindowState;
    class KeyboardState;
}

#include "../DObject.h"

namespace dengine {
    class Events : public DObject {
    private:
        std::unique_ptr<WindowState> windowState;
        std::unique_ptr<KeyboardState> keyboardState;
        std::unique_ptr<MouseState> mouseState;
    public:
        Events(std::unique_ptr<WindowState> windowState, std::unique_ptr<KeyboardState> keyboardState,
               std::unique_ptr<MouseState> mouseState);

        const WindowState & getWindowState() const;

        const KeyboardState & getKeyboardState() const;

        const MouseState & getMouseState() const;
    };
}

#endif //DENGINE_EVENTSSTATE_H
