#include "MouseEventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_MOUSEBUTTONEVENTINFO_H
#define DENGINE_MOUSEBUTTONEVENTINFO_H


class MouseButtonEventInfo : public MouseEventInfo {
private:
    unsigned int buttonCode;
public:
    MouseButtonEventInfo(int, int, unsigned int);
    unsigned int getButtonCode();
};


#endif //DENGINE_MOUSEBUTTONEVENTINFO_H
