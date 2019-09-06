//
// Created by wcobalt on 7/9/19.
//
#include <memory>

#ifndef DENGINE_WINDOWSTATEBUILDER_H
#define DENGINE_WINDOWSTATEBUILDER_H

namespace dengine {
    class WindowState;
}

namespace dengine {
    class WindowStateBuilder {
    public:
        virtual void setMaximized(bool wasMaximized) = 0;

        virtual void setWindowed(bool wasWindowed) = 0;

        virtual void setIconified(bool wasIconified) = 0;

        virtual void setResized(bool wasResized) = 0;

        virtual void setGotFocus(bool gotFocus) = 0;

        virtual void setLostFocus(bool lostFocus) = 0;

        virtual void setClosing(bool isClosing) = 0;

        virtual std::shared_ptr<WindowState> build() const = 0;
    };
}

#endif //DENGINE_WINDOWSTATEBUILDER_H
