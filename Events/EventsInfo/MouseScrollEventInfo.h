#include "MouseEventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_MOUSESCROLLEVENTINFO_H
#define DENGINE_MOUSESCROLLEVENTINFO_H


class MouseScrollEventInfo : public MouseEventInfo {
private:
    int scrollPoints;
public:
    MouseScrollEventInfo(int x, int y, int scrollPoints);
    int getScrollPoints();
};


#endif //DENGINE_MOUSESCROLLEVENTINFO_H
