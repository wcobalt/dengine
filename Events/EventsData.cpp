//
// Created by wcobalt on 19.09.18.
//

#include "EventsData.h"

std::set<int> EventsData::getPressedKeys() {
    return pressedKeys;
}

std::set<int> EventsData::getReleasedKeys() {
    return releasedKeys;
}

std::set<int> EventsData::getPressedButtons() {
    return pressedButtons;
}

std::set<int> EventsData::getReleasedButtons() {
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

MousePosition EventsData::getMousePosition() {
    //@todo check is it right
    return mousePosition;
}

void EventsData::addPressedKey(int keyCode) {
    pressedKeys.insert(keyCode);
}

void EventsData::addReleasedKey(int keyCode) {
    releasedKeys.insert(keyCode);
}

void EventsData::addPressedButton(int buttonNumber) {
    pressedButtons.insert(buttonNumber);
}

void EventsData::addReleasedButton(int buttonNumber) {
    releasedButtons.insert(buttonNumber);
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

void EventsData::setMousePosition(MousePosition mousePosition) {
    this->mousePosition = mousePosition;
}
