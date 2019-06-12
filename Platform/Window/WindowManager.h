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
}

#include "../../DObject.h"

namespace dengine::platform::window {
    enum WindowGeometryState {
        NORMAL,
        MAXIMIZED_HORIZONTAL,
        MAXIMIZED_VERTICAL,
        MAXIMIZED_BOTH,
        MINIMIZED,
        FULLSCREEN,
        HIDDEN_TO_TRAY,
        HIDDEN
    };

    class WindowManager : public DObject {
    public:
        virtual void setDecorated(bool isDecorated) = 0;

        virtual void setCursorVisible(bool isVisible) = 0;

        virtual void setWindowPosition(int x, int y) = 0;

        virtual void setWindowSize(uint width, uint height) = 0;

        virtual void setIcon(const long* buffer, int length) = 0;

        virtual void setRatio(uint width, uint height) = 0;

        //@todo implement
        virtual void setTrayIcon(const long* buffer, int length) = 0;

        //@todo implement
        virtual void setTrayName(const std::string& name) = 0;

        //@todo implement
        virtual void sendNotification(const std::string& message) = 0;

        virtual void setWindowTitle(const std::string &title) = 0;

        virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;

        virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;

        virtual void setWindowGeometryState(WindowGeometryState windowGeometryState) = 0;

        virtual void centerWindow() = 0;

        virtual void destroyWindow() = 0;

        virtual std::vector<uint> getScreenResolution() = 0;

        virtual bool isDecorated() const = 0;

        virtual bool isCursorVisible() const = 0;

        virtual std::vector<int> getWindowPosition() const = 0;

        virtual std::vector<int> getClientAreaPosition() const = 0;

        virtual std::vector<uint> getWindowSize() const = 0;

        virtual std::vector<uint> getRatio() const = 0;

        virtual const std::string &getWindowTitle() const = 0;

        virtual std::vector<uint> getMaximumSize() const = 0;

        virtual std::vector<uint> getMinimumSize() const = 0;

        virtual WindowGeometryState getWindowGeometryState() const = 0;

        virtual std::shared_ptr<dengine::events::MouseState> getMouseState() const = 0;

        virtual std::shared_ptr<dengine::events::KeyboardState> getKeyboardState() const = 0;

        virtual std::shared_ptr<dengine::events::WindowState> getWindowState() const = 0;

        virtual ~WindowManager();
    };
}

#endif //DENGINE_WINDOWMANAGER_H
