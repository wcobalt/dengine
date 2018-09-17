#include "../EventsHandlers/MouseEventsHandler.h"
//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_MOUSEEVENTSADAPTER_H
#define DENGINE_MOUSEEVENTSADAPTER_H


class MouseEventsAdapter : public MouseEventsHandler {
public:
    virtual void mouseOver(MouseEventInfo info);
    virtual void mouseOut(MouseEventInfo info);
    virtual void mouseMove(MouseEventInfo info);
    virtual void mouseButtonPressed(MouseButtonEventInfo info);
    virtual void mouseButtonReleased(MouseButtonEventInfo info);
    virtual void mouseButtonClicked(MouseButtonEventInfo info);
    virtual void mouseDrag(MouseEventInfo info);
    virtual void mouseDraggingStart(MouseEventInfo info);
    virtual void mouseDraggingEnd(MouseEventInfo info);
    virtual void mouseScroll(MouseScrollEventInfo info);
};


#endif //DENGINE_MOUSEEVENTSADAPTER_H
