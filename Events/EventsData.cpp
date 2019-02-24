//
// Created by wcobalt on 19.09.18.
//

#include "EventsData.h"

EventsData::EventsData() {
    windowMaximized = windowMinimized = windowWindowed = false;

    windowResized = false;

    windowFocused = false;

    mouseWheelDirection = 0;

    windowClosing = false;
}

std::set<int> EventsData::getPressedKeys() const {
    return pressedKeys;
}

std::set<int> EventsData::getReleasedKeys() const {
    return releasedKeys;
}

std::set<int> EventsData::getPressedButtons() const {
    return pressedButtons;
}

std::set<int> EventsData::getReleasedButtons() const {
    return releasedButtons;
}

bool EventsData::isWindowMaximized() const {
    return windowMaximized;
}

bool EventsData::isWindowMinimized() const {
    return windowMinimized;
}

bool EventsData::isWindowWindowed() const {
    return windowWindowed;
}

bool EventsData::isWindowResized() const {
    return windowResized;
}

bool EventsData::isWindowFocused() const {
    return windowFocused;
}

int EventsData::getMouseWheelDirection() const {
    return mouseWheelDirection;
}

const MousePosition& EventsData::getMousePosition() const {
    return *mousePosition;
}

bool EventsData::isWindowClosing() const {
    return windowClosing;
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

void EventsData::setWindowMaximized(bool windowMaximized) {
    this->windowMaximized = windowMaximized;
}

void EventsData::setWindowMinimized(bool windowMinimized) {
    this->windowMinimized = windowMinimized;
}

void EventsData::setWindowWindowed(bool windowWindowed) {
    this->windowWindowed = windowWindowed;
}

void EventsData::setWindowResized(bool windowResized) {
    this->windowResized = windowResized;
}

void EventsData::setWindowFocused(bool isWindowFocused) {
    this->windowFocused = isWindowFocused;
}

void EventsData::setMouseWheelDirection(int mouseWheelDirection) {
    this->mouseWheelDirection = mouseWheelDirection;
}

void EventsData::setMousePosition(const MousePosition& mousePosition) {
    this->mousePosition = &mousePosition;
    //что происходит если this-mnousePosiiotn& не const и мы делаем &(this->mousePosition)=mousePosition
}

void EventsData::setWindowClosing(bool windowClosing) {
    this->windowClosing = windowClosing;
}