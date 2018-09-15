#include <GL/glx.h>
#include <X11/Xlib.h>
//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H


class WindowAccessor {
public:
    virtual int initialize(int, int, int, int, GLint[]) = 0;
};


#endif //DENGINE_WINDOWACCESSOR_H
