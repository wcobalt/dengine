//
// Created by wcobalt on 23.05.19.
//

#ifndef DENGINE_WINDOWSTATE_H
#define DENGINE_WINDOWSTATE_H

#include "../../DObject.h"

namespace dengine {
    class WindowState : DObject {
    public:
        virtual bool wasMaximized() const = 0;

        virtual bool wasWindowed() const = 0;

        virtual bool wasIconified() const = 0;

        virtual bool wasResized() const = 0;

        virtual bool gotFocus() const = 0;

        virtual bool lostFocus() const = 0;

        virtual bool isClosing() const = 0;

        virtual bool wasMoved() const = 0;

        virtual bool wasHiddenToTray() const = 0;
    };
}

#endif //DENGINE_WINDOWSTATE_H
