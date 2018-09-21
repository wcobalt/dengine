//
// Created by wcobalt on 19.09.18.
//
#include <set>
#include <map>
#include "MousePosition.h"

#ifndef DENGINE_EVENTSDATA_H
#define DENGINE_EVENTSDATA_H


class EventsData {
private:
    std::set<int> pressedKeys;
    std::set<int> releasedKeys;

    std::set<int> pressedButtons;
    std::set<int> releasedButtons;

    bool windowMaximized, windowMinimized,
         windowWindowed;

    bool windowResized;

    bool isWindowGotFocus;
    bool isWindowLostFocus;

    int mouseWheelDirection;

    MousePosition mousePosition;
public:
    EventsData() = default;

    std::set<int> getPressedKeys();
    std::set<int> getReleasedKeys();
    std::set<int> getPressedButtons();
    std::set<int> getReleasedButtons();
    bool isWindowMaximized();
    bool isWindowMinimized();
    bool isWindowWindowed();
    bool isWindowResized();
    bool windowGotFocus();
    bool windowLostFocus();
    int getMouseWheelDirection();
    MousePosition getMousePosition();

    void addPressedKey(int keyCode);
    void addReleasedKey(int keyCode);
    void addPressedButton(int buttonNumber);
    void addReleasedButton(int buttonNumber);
    void setWindowMaximized(bool isWindowMaximized);
    void setWindowMinimized(bool isWindowMinimized);
    void setWindowWindowed(bool isWindowWindowed);
    void setWindowResized(bool isWindowResized);
    void setWindowGotFocus(bool isWindowGotFocus);
    void setWindowLostFocus(bool isWindowLostFocus);
    void setMouseWheelDirection(int mouseWheelDirection);
    void setMousePosition(MousePosition mousePosition);
};


#endif //DENGINE_EVENTSDATA_H
