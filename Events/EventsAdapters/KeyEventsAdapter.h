#include "../EventsHandlers/KeyEventsHandler.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_KEYEVENTSADAPTER_H
#define DENGINE_KEYEVENTSADAPTER_H


class KeyEventsAdapter : public KeyEventsHandler {
public:
    virtual void keyPressed(KeyEventInfo info);
    virtual void keyReleased(KeyEventInfo info);
    virtual void keyChecked(KeyEventInfo info);
};


#endif //DENGINE_KEYEVENTSADAPTER_H
