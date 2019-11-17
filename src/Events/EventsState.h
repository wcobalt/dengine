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
    class EventsState : public DObject {
    private:
        std::shared_ptr<WindowState> windowState;
        std::shared_ptr<KeyboardState> keyboardState;
        std::shared_ptr<MouseState> mouseState;
    public:
        EventsState(std::shared_ptr<WindowState> windowState, std::shared_ptr<KeyboardState> keyboardState,
                std::shared_ptr<MouseState> mouseState);

        std::shared_ptr<WindowState> getWindowState() const;

        std::shared_ptr<KeyboardState> getKeyboardState() const;

        std::shared_ptr<MouseState> getMouseState() const;
    };
}

#endif //DENGINE_EVENTSSTATE_H
