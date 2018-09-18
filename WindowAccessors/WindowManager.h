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
    WindowManager(WindowAccessor*);
    WindowAccessor* getWindowAccessor();
};


#endif //DENGINE_WINDOWMANAGER_H
