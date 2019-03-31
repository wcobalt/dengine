//
// Created by wcobalt on 19.09.18.
//
#include <set>
#include <memory>

#ifndef DENGINE_EVENTSDATA_H
#define DENGINE_EVENTSDATA_H

#include "MousePosition.h"

namespace dengine::events {
    using std::set;
    using std::shared_ptr;

    class EventsData {
    private:
        set<int> pressedKeys;
        set<int> releasedKeys;

        set<int> pressedButtons;
        set<int> releasedButtons;

        bool windowMaximized, windowMinimized,
                windowWindowed;

        bool windowResized;

        bool windowFocused;

        int mouseWheelDirection;

        shared_ptr<const MousePosition> mousePosition;

        bool windowClosing;
    public:
        EventsData();

        set<int> getPressedKeys() const;

        set<int> getReleasedKeys() const;

        set<int> getPressedButtons() const;

        set<int> getReleasedButtons() const;

        bool isWindowMaximized() const;

        bool isWindowMinimized() const;

        bool isWindowWindowed() const;

        bool isWindowResized() const;

        bool isWindowFocused() const;

        int getMouseWheelDirection() const;

        shared_ptr<const MousePosition> getMousePosition() const;

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

        void setMousePosition(shared_ptr<const MousePosition> mousePosition);

        void setWindowClosing(bool windowClosing);
    };
}

#endif //DENGINE_EVENTSDATA_H
