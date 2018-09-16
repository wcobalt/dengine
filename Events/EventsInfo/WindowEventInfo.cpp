//
// Created by wcobalt on 16.09.18.
//

#include "WindowEventInfo.h"

WindowEventInfo::WindowEventInfo(int x, int y, unsigned int width, unsigned int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int WindowEventInfo::getX() {
    return x;
}

int WindowEventInfo::getY() {
    return y;
}

unsigned int WindowEventInfo::getWidth() {
    return width;
}

unsigned int WindowEventInfo::getHeight() {
    return height;
}