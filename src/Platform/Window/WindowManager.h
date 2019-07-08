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
        namespace mouse {
            class MouseState;
        }

        namespace keyboard {
            class KeyboardState;
        }

        namespace window {
            class WindowState;
        }
    }
}

#include "../../DObject.h"

namespace dengine::platform::window {
    class WindowManager : public DObject {
    public:
        static const int NORMAL = 0,
                ICONIFIED = 1,
                HIDDEN_TO_TRAY = 2,
                MAXIMIZED_HORIZONTAL = 3,
                MAXIMIZED_VERTICAL = 4,
                MAXIMIZED_BOTH = 5;

        virtual void setVisible(bool isVisible) = 0;

        virtual void setDecorated(bool isDecorated) = 0;

        virtual void setCursorVisible(bool isVisible) = 0;

        virtual void setPosition(int x, int y) = 0;

        virtual void setSize(uint width, uint height) = 0;

        virtual void setIcon(const long* buffer, int length) = 0;

        virtual void setRatio(uint width, uint height) = 0;

        //@todo implement
        virtual void setTrayIcon(const long* buffer, int length) = 0;

        //@todo implement
        virtual void setTrayName(const std::string& name) = 0;

        //@todo implement
        virtual void sendNotification(const std::string& message) = 0;

        virtual void setTitle(const std::string &title) = 0;

        virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;

        virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;

        virtual void setGeometryState(int windowGeometryState) = 0;

        virtual void setFullscreenEnabled(bool isFullscreenEnabled) = 0;

        virtual void setMaximizationState(int maximization) = 0;

        virtual void center() = 0;

        virtual void destroy() = 0;

        virtual bool isVisible() const = 0;

        virtual std::vector<uint> getScreenResolution() = 0;

        virtual bool isDecorated() const = 0;

        virtual bool isCursorVisible() const = 0;

        virtual std::vector<int> getPosition() const = 0;

        virtual std::vector<int> getClientAreaPosition() const = 0;

        virtual std::vector<uint> getSize() const = 0;

        virtual std::vector<uint> getRatio() const = 0;

        virtual const std::string &getTitle() const = 0;

        virtual std::vector<uint> getMaximumSize() const = 0;

        virtual std::vector<uint> getMinimumSize() const = 0;

        virtual int getGeometryState() const = 0;

        virtual bool isFullscreenEnabled() const = 0;

        virtual int getMaximizationState() const = 0;

        virtual std::shared_ptr<dengine::events::mouse::MouseState> getMouseState() const = 0;

        virtual std::shared_ptr<dengine::events::keyboard::KeyboardState> getKeyboardState() const = 0;

        virtual std::shared_ptr<dengine::events::window::WindowState> getWindowState() const = 0;

        virtual ~WindowManager();
    };
}

#endif //DENGINE_WINDOWMANAGER_H
