#include "EventParameters.h"
//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_MOUSEEVENTPARAMETERS_H
#define DENGINE_MOUSEEVENTPARAMETERS_H


class MouseEventParameters : public EventParameters {
private:
    int x;
    int y;
public:
    MouseEventParameters(int x, int y);
    int getX();
    int getY();
};


#endif //DENGINE_MOUSEEVENTPARAMETERS_H
