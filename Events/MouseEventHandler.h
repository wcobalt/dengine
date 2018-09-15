#include "EventHandler.h"
//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_MOUSEEVENTHANDLER_H
#define DENGINE_MOUSEEVENTHANDLER_H


class MouseEventHandler : public EventHandler {
public:
    virtual void handle(MouseEventParameters) = 0;
};


#endif //DENGINE_MOUSEEVENTHANDLER_H
