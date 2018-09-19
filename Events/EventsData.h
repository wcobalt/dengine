//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <map>

#ifndef DENGINE_EVENTSDATA_H
#define DENGINE_EVENTSDATA_H


class EventsData {
private:
    std::vector<int> pressedKeys;
    std::vector<int> releasedKeys;

    std::vector<int> pressedButtons;
    std::vector<int> releasedButtons;

    bool windowMaximized, windowMinimized,
         windowWindowed;

    bool windowResized;

    bool isWindowGotFocus;
    bool isWindowLostFocus;

    int mouseWheelDirection;
    int mouseX, mouseY;
public:
    std::vector<int> getPressedKeys();
    std::vector<int> getReleasedKeys();
    std::vector<int> getPressedButtons();
    std::vector<int> getReleasedButtons();
    bool isWindowMaximized();
    bool isWindowMinimized();
    bool isWindowWindowed();
    bool isWindowResized();
    bool windowGotFocus();
    bool windowLostFocus();
    int getMouseWheelDirection();
    std::vector<int> getMouseCoordinates();

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
    void setMouseCoords(int mouseX, int mouseY);
};


#endif //DENGINE_EVENTSDATA_H
