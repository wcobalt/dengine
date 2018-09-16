#include "EventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_WINDOWEVENTINFO_H
#define DENGINE_WINDOWEVENTINFO_H


class WindowEventInfo : public EventInfo {
private:
    int x;
    int y;
    unsigned int width;
    unsigned int height;
public:
    WindowEventInfo(int, int, unsigned int, unsigned int);
    int getX();
    int getY();
    unsigned int getWidth();
    unsigned int getHeight();
};


#endif //DENGINE_WINDOWEVENTINFO_H
