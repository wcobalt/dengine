#include "WindowAccessor.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_WINDOWMANAGER_H
#define DENGINE_WINDOWMANAGER_H


class WindowManager {
private:
    WindowAccessor* windowAccessor;
public:
    virtual WindowAccessor* getWindowAccessor() = 0;
};


#endif //DENGINE_WINDOWMANAGER_H
