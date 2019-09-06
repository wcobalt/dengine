//
// Created by wcobalt on 7/9/19.
//
#include <memory>

#ifndef DENGINE_DEFAULTWINDOWSTATEBUILDER_H
#define DENGINE_DEFAULTWINDOWSTATEBUILDER_H

#include "WindowStateBuilder.h"

namespace dengine {
    class WindowState;
}

namespace dengine {
    class DefaultWindowStateBuilder : public WindowStateBuilder {
    private:
        bool wasMaximized, wasIconified,
                wasWindowed, wasResized,
                gotFocus, lostFocus,
                isClosing, wasMoved;
    public:
        void setMaximized(bool wasMaximized);

        void setWindowed(bool wasWindowed);

        void setIconified(bool wasIconified);

        void setResized(bool wasResized);

        void setGotFocus(bool gotFocus);

        void setLostFocus(bool lostFocus);

        void setClosing(bool isClosing);

        void setMoved(bool wasMoved) override;

        std::shared_ptr<WindowState> build() const;
    };
}

#endif //DENGINE_DEFAULTWINDOWSTATEBUILDER_H
