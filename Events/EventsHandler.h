//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_EVENTHANDLER_H
#define DENGINE_EVENTHANDLER_H


class EventHandler {
public:
    virtual void handle(EventParameters) = 0;
};


#endif //DENGINE_EVENTHANDLER_H
