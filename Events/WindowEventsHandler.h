#include "EventsHandler.h"
#include "WindowEventInfo.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_WINDOWEVENTSHANDLER_H
#define DENGINE_WINDOWEVENTSHANDLER_H


class WindowEventsHandler : public EventsHandler {
    virtual void windowOpened(WindowEventInfo info) = 0;
    virtual void windowClosed(WindowEventInfo info) = 0;
    virtual void windowMaximized(WindowEventInfo info) = 0;
    virtual void windowMinimized(WindowEventInfo info) = 0;
    virtual void windowWindowed(WindowEventInfo info) = 0;
    virtual void windowMove(WindowEventInfo info) = 0;
    virtual void windowGotFocus(WindowEventInfo info) = 0;
    virtual void windowLostFocus(WindowEventInfo info) = 0;
    virtual void windowResized(WindowEventInfo info) = 0;
};


#endif //DENGINE_WINDOWEVENTSHANDLER_H
