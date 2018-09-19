//
// Created by wcobalt on 19.09.18.
//

#include "EventsData.h"

std::vector<int> EventsData::getPressedKeys() {
    return pressedKeys;
}

std::vector<int> EventsData::getReleasedKeys() {
    return releasedKeys;
}

std::vector<int> EventsData::getPressedButtons() {
    return pressedButtons;
}

std::vector<int> EventsData::getReleasedButtons() {
    return releasedButtons;
}

bool EventsData::isWindowMaximized() {
    return windowMaximized;
}

bool EventsData::isWindowMinimized() {
    return windowMinimized;
}

bool EventsData::isWindowWindowed() {
    return windowWindowed;
}

bool EventsData::isWindowResized() {
    return windowResized;
}

bool EventsData::windowGotFocus() {
    return isWindowGotFocus;
}

bool EventsData::windowLostFocus() {
    return isWindowLostFocus;
}

int EventsData::getMouseWheelDirection() {
    return mouseWheelDirection;
}

std::vector<int> EventsData::getMouseCoordinates() {
    //@todo check is it right
    return std::vector<int>{mouseX, mouseY};
}


void EventsData::addPressedKey(int keyCode) {
    pressedKeys.push_back(keyCode);
}

void EventsData::addReleasedKey(int keyCode) {
    releasedKeys.push_back(keyCode);
}

void EventsData::addPressedButton(int buttonNumber) {
    pressedButtons.push_back(buttonNumber);
}

void EventsData::addReleasedButton(int buttonNumber) {
    releasedButtons.push_back(buttonNumber);
}

void EventsData::setWindowMaximized(bool isWindowMaximized) {
    windowMaximized = isWindowMaximized;
}

void EventsData::setWindowMinimized(bool isWindowMinimized) {
    windowMinimized = isWindowMinimized;
}

void EventsData::setWindowWindowed(bool isWindowWindowed) {
    windowWindowed = isWindowWindowed;
}

void EventsData::setWindowResized(bool isWindowResized) {
    windowResized = isWindowResized;
}

void EventsData::setWindowGotFocus(bool isWindowGotFocus) {
    this->isWindowGotFocus = isWindowGotFocus;
}

void EventsData::setWindowLostFocus(bool isWindowLostFocus) {
    this->isWindowLostFocus = isWindowLostFocus;
}

void EventsData::setMouseWheelDirection(int mouseWheelDirection) {
    this->mouseWheelDirection = mouseWheelDirection;
}

void EventsData::setMouseCoordinates(int mouseX, int mouseY) {
    this->mouseX = mouseX;
    this->mouseY = mouseY;
}
