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

bool EventsData::isWindowFocused() {
    return windowFocused;
}

int EventsData::getMouseWheelDirection() {
    return mouseWheelDirection;
}

MousePosition EventsData::getMousePosition() {
    //@todo check is it right
    return mousePosition;
}

bool EventsData::isWindowClosing() {
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

void EventsData::setMousePosition(MousePosition mousePosition) {
    this->mousePosition = mousePosition;
}

void EventsData::setWindowClosing(bool windowClosing) {
    this->windowClosing = windowClosing;
}