//
// Created by wcobalt on 19.09.18.
//
#include <set>
#include <memory>

#ifndef DENGINE_EVENTSDATA_H
#define DENGINE_EVENTSDATA_H

#include "../DObject.h"
#include "MousePosition.h"

namespace dengine::events {
    class EventsData : public DObject {
    private:
        std::set<int> pressedKeys;
        std::set<int> releasedKeys;

        std::set<int> pressedButtons;
        std::set<int> releasedButtons;

        bool windowMaximized, windowMinimized,
                windowWindowed;

        bool windowResized;

        bool windowFocused;

        int mouseWheelDirection;

        std::shared_ptr<const MousePosition> mousePosition;

        bool windowClosing;
    public:
        EventsData();

        std::set<int> getPressedKeys() const;

        std::set<int> getReleasedKeys() const;

        std::set<int> getPressedButtons() const;

        std::set<int> getReleasedButtons() const;

        bool isWindowMaximized() const;

        bool isWindowMinimized() const;

        bool isWindowWindowed() const;

        bool isWindowResized() const;

        bool isWindowFocused() const;

        int getMouseWheelDirection() const;

        std::shared_ptr<const MousePosition> getMousePosition() const;

        bool isWindowClosing() const;

        void addPressedKey(int keyCode);

        void addReleasedKey(int keyCode);

        void addPressedButton(int buttonNumber);

        void addReleasedButton(int buttonNumber);

        void setWindowMaximized(bool windowMaximized);

        void setWindowMinimized(bool windowMinimized);

        void setWindowWindowed(bool windowWindowed);

        void setWindowResized(bool windowResized);

        void setWindowFocused(bool isWindowFocused);

        void setMouseWheelDirection(int mouseWheelDirection);

        void setMousePosition(std::shared_ptr<const MousePosition> mousePosition);

        void setWindowClosing(bool windowClosing);
    };
}

#endif //DENGINE_EVENTSDATA_H
