#include "EventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_MOUSEEVENTINFO_H
#define DENGINE_MOUSEEVENTINFO_H


class MouseEventInfo : public EventInfo {
private:
    int x;
    int y;
public:
    MouseEventInfo(int, int);
    int getX();
    int getY();
};


#endif //DENGINE_MOUSEEVENTINFO_H
