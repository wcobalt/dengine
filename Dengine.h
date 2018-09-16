#include <string>
#include "WindowAccessors/WindowManager.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_DENGINE_H
#define DENGINE_DENGINE_H


class Dengine {
private:
    int fps;
    WindowManager* windowManager;
public:
    Dengine();
    //@todo to Window class
    //@todo getXXX() add
    void setWindowTitle(std::string);
    void setWindowPosition(int, int);
    void setWindowSize(unsigned int, unsigned int);
    void setFPS(int);
    int getFPS();
    void setWindowManager(WindowManager*);
    void start();
};


#endif //DENGINE_DENGINE_H
