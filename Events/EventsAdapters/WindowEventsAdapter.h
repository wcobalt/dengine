#include "../EventsHandlers/WindowEventsHandler.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_WINDOWEVENTSADAPTER_H
#define DENGINE_WINDOWEVENTSADAPTER_H


class WindowEventsAdapter : public WindowEventsHandler {
public:
    virtual void windowOpened(WindowEventInfo info);
    virtual void windowClosed(WindowEventInfo info);
    virtual void windowMaximized(WindowEventInfo info);
    virtual void windowMinimized(WindowEventInfo info);
    virtual void windowWindowed(WindowEventInfo info);
    virtual void windowMove(WindowEventInfo info);
    virtual void windowGotFocus(WindowEventInfo info);
    virtual void windowLostFocus(WindowEventInfo info);
    virtual void windowResized(WindowEventInfo info);
};


#endif //DENGINE_WINDOWEVENTSADAPTER_H
