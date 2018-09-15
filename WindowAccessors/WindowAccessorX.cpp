//For this libraries you should install libgl1-mesa-dev
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include "WindowAccessorX.h"
#include <iostream>

//X11 windowAccessor

WindowAccessorX::WindowAccessorX() {
    int a;std::cout<<"sss";
}

int WindowAccessorX::initialize(int x, int y, int width, int height, GLint attributes[]) {
    std::cout<<"sss";
    return 0;
}