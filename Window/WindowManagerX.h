//
// Created by wcobalt on 15.09.18.
//

#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <string>
#include <memory>
#include <vector>

#ifndef DENGINE_WINDOWACCESSORX_H
#define DENGINE_WINDOWACCESSORX_H

namespace dengine {
    namespace events {
        class EventsData;
    }

    namespace graphics {
        class PNGImage;
    }
}

#include "WindowManager.h"

namespace dengine::window {
    struct PropertyData {
        unsigned char *data;
        ulong numberOfItems;

        PropertyData(unsigned char *data, ulong numberOfItems) {
            this->data = data;
            this->numberOfItems = numberOfItems;
        }

        ~PropertyData() {
            delete[] data;
        }
    };

    class WindowManagerX : public WindowManager {
    private:
        Display *display;
        Window rootWindow;
        XVisualInfo *xVisualInfo;
        Colormap colorMap;
        XSetWindowAttributes xSetWindowAttributes;
        Window window;
        GLXContext glXContext;

        Atom wmDeleteWindow;

        uint lastWidth, lastHeight;

        std::string title;

        PropertyData getProperty(const char *propertyName, long offset, long size, Window window) const;

        void setMinimumAndMaximumSize(uint maximumWidth, uint maximumHeight,
                                      uint minimumWidth, uint minimumHeight);

    public:
        WindowManagerX(int x, int y, uint width, uint height, const std::string& title);

        void setVisible(bool isVisible);

        void setDecorated(bool isDecorated);

        void setCursorVisible(bool isVisible);

        void setWindowPosition(int x, int y);

        void setSize(uint width, uint height);

        void setIcon(const dengine::graphics::PNGImage& image);

        void setHiddenToTray(bool isHidden);

        void setWindowTitle(const std::string &title);

        void setMaximumSize(uint maximumWidth, uint maximumHeight);

        void setMinimumSize(uint minimumWidth, uint minimumHeight);

        void setFullscreenEnabled(bool isEnabled);

        void destroyWindow();

        bool isVisible() const;

        bool isDecorated() const;

        bool isCursorVisible() const;

        std::vector<int> getWindowPosition() const;

        std::vector<int> getClientAreaPosition() const;

        std::vector<uint> getSize() const;

        bool isHiddenToTray() const;

        const std::string &getWindowTitle() const;

        std::vector<uint> getMaximumSize() const;

        std::vector<uint> getMinimumSize() const;

        bool isFullscreenEnabled() const;

        //@todo GLXContext

        std::shared_ptr<dengine::events::MouseState> getMouseState() const;

        std::shared_ptr<dengine::events::KeyboardState> getKeyboardState() const;

        std::shared_ptr<dengine::events::WindowState> getWindowState() const;

        ~WindowManagerX();
    };
}

#endif //DENGINE_WINDOWACCESSORX_H
