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

    bool windowClosing;
public:
    EventsData();

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
    bool isWindowClosing();

    void addPressedKey(int keyCode);
    void addReleasedKey(int keyCode);
    void addPressedButton(int buttonNumber);
    void addReleasedButton(int buttonNumber);
    void setWindowMaximized(bool windowMaximized);
    void setWindowMinimized(bool windowMinimized);
    void setWindowWindowed(bool windowWindowed);
    void setWindowResized(bool windowResized);
    void setWindowGotFocus(bool isWindowGotFocus);
    void setWindowLostFocus(bool isWindowLostFocus);
    void setMouseWheelDirection(int mouseWheelDirection);
    void setMousePosition(MousePosition mousePosition);
    void setWindowClosing(bool windowClosing);
};


#endif //DENGINE_EVENTSDATA_H
