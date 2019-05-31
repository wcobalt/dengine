//
// Created by wcobalt on 16.09.18.
//

#include <string>
#include <vector>
#include <memory>

#ifndef DENGINE_WINDOWMANAGER_H
#define DENGINE_WINDOWMANAGER_H

namespace dengine {
    namespace events {
        class EventsData;
        class MouseState;
        class KeyboardState;
        class WindowState;
    }

    namespace window {
        class WindowAccessor;
    }

    namespace graphics {
        class PNGImage;
    }
}

#include "../../DObject.h"

namespace dengine::platform::window {
    class WindowManager : public DObject {
    public:
        virtual void setVisible(bool isVisible) = 0;

        virtual void setDecorated(bool isDecorated) = 0;

        virtual void setCursorVisible(bool isVisible) = 0;

        virtual void setWindowPosition(int x, int y) = 0;

        virtual void setSize(uint width, uint height) = 0;

        virtual void setIcon(const dengine::graphics::PNGImage& image) = 0;

        virtual void setHiddenToTray(bool isHidden) = 0;

        virtual void setWindowTitle(const std::string &title) = 0;

        virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;

        virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;

        virtual void setFullscreenEnabled(bool isEnabled) = 0;

        virtual void destroyWindow() = 0;

        virtual bool isVisible() const = 0;

        virtual bool isDecorated() const = 0;

        virtual bool isCursorVisible() const = 0;

        virtual std::vector<int> getWindowPosition() const = 0;

        virtual std::vector<int> getClientAreaPosition() const = 0;

        virtual std::vector<uint> getSize() const = 0;

        virtual bool isHiddenToTray() const = 0;

        virtual const std::string &getWindowTitle() const = 0;

        virtual std::vector<uint> getMaximumSize() const = 0;

        virtual std::vector<uint> getMinimumSize() const = 0;

        virtual bool isFullscreenEnabled() const = 0;

        virtual std::shared_ptr<dengine::events::MouseState> getMouseState() const = 0;

        virtual std::shared_ptr<dengine::events::KeyboardState> getKeyboardState() const = 0;

        virtual std::shared_ptr<dengine::events::WindowState> getWindowState() const = 0;

        virtual ~WindowManager() = 0;
    };
}

#endif //DENGINE_WINDOWMANAGER_H
