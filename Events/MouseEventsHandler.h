#include "EventsHandler.h"
#include "MouseEventInfo.h"
#include "MouseButtonEventInfo.h"
#include "MouseScrollEventInfo.h"

//
// Created by wcobalt on 16.09.18.
//

#ifndef DENGINE_MOUSEEVENTSHANDLER_H
#define DENGINE_MOUSEEVENTSHANDLER_H


class MouseEventsHandler : public EventsHandler {
public:
    virtual void mouseOver(MouseEventInfo info) = 0;
    virtual void mouseOut(MouseEventInfo info) = 0;
    virtual void mouseMove(MouseEventInfo info) = 0;
    virtual void mouseButtonPressed(MouseButtonEventInfo info) = 0;
    virtual void mouseButtonReleased(MouseButtonEventInfo info) = 0;
    virtual void mouseButtonClicked(MouseButtonEventInfo info) = 0;
    //@todo MouseDragEventInfo with startX and startY
    virtual void mouseDrag(MouseEventInfo info) = 0;//@todo is dragging only my left mouse button
    virtual void mouseDraggingStart(MouseEventInfo info) = 0;
    virtual void mouseDraggingEnd(MouseEventInfo info) = 0;
    virtual void mouseScroll(MouseScrollEventInfo info) = 0;
};


#endif //DENGINE_MOUSEEVENTSHANDLER_H
