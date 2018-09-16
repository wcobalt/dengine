#include "EventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_KEYEVENTINFO_H
#define DENGINE_KEYEVENTINFO_H


class KeyEventInfo : public EventInfo {
private:
    unsigned int keyCode;
public:
    KeyEventInfo(unsigned int);
    unsigned int getKeyCode();
};


#endif //DENGINE_KEYEVENTINFO_H
