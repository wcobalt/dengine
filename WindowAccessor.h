#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H


class WindowAccessor {
public:
    virtual int initialize(int, int, unsigned int, unsigned int, GLint[], long, std::string) = 0;
};


#endif //DENGINE_WINDOWACCESSOR_H
