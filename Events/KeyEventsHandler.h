#include "EventsHandler.h"
#include "KeyEventInfo.h"

//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_KEYEVENTSHANDLER_H
#define DENGINE_KEYEVENTSHANDLER_H


class KeyEventsHandler : public EventsHandler {
    virtual void keyPressed(KeyEventInfo info) = 0;
    virtual void keyReleased(KeyEventInfo info) = 0;
    virtual void keyChecked(KeyEventInfo info) = 0;
};


#endif //DENGINE_KEYEVENTSHANDLER_H
