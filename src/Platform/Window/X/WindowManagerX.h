//
// Created by wcobalt on 15.09.18.
//

#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <string>
#include <memory>
#include <vector>

#ifndef DENGINE_WINDOWMANAGERX_H
#define DENGINE_WINDOWMANAGERX_H

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

#include "../WindowManager.h"

namespace dengine::platform::window::x {
    class WindowManagerX : public WindowManager {
    private:
        const uint DEFAULT_SCREEN = 0;
        const uint DEFAULT_WINDOW_DEPTH = 0;
        const int VISUAL_DEPTH = 24;

        Display *display;
        Window rootWindow;
        XVisualInfo* visualInfo;
        Window window;
        GLXContext glXContext;
        XSizeHints* xSizeHints;

        uint lastWidth, lastHeight;

        int lastX, lastY;

        std::string title;

        bool mIsCursorVisible;
        bool mIsDecorated;
        bool mIsVisible;

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

        PropertyData getProperty(const char *propertyName, Window window) const;

        void setSizeHints(uint maximumWidth, uint maximumHeight,
                          uint minimumWidth, uint minimumHeight,
                          uint ratioX, uint ratioY);

        void setWindowBounds(int x, int y, uint width, uint height);
        void sendEvent(int type, const char* messageTypeAtomName, int format, long* data, long eventMask,
                Window from, Window to);
        void setMaximized(bool mode, Atom atom);
        bool find(long needle, const PropertyData& haystack) const;
    public:
        WindowManagerX(int x, int y, uint width, uint height, const std::string& title);

        void setVisible(bool isVisible);

        void setDecorated(bool isDecorated);

        void setCursorVisible(bool isVisible);

        void setPosition(int x, int y);

        void setSize(uint width, uint height);

        void setIcon(const long* buffer, int length);

        void setRatio(uint ratioX, uint ratioY);

        void setTrayIcon(const long* buffer, int length);

        void setTrayName(const std::string& name);

        void sendNotification(const std::string& message);

        void setTitle(const std::string &title);

        void setMaximumSize(uint maximumWidth, uint maximumHeight);

        void setMinimumSize(uint minimumWidth, uint minimumHeight);

        void setGeometryState(int windowGeometryState);

        void setFullscreenEnabled(bool isFullscreenEnabled);

        void setMaximizationState(int maximization);

        void center();

        void destroy();

        bool isVisible() const;//cache v

        std::vector<uint> getScreenResolution();//non-cache v

        bool isDecorated() const;//cache v

        bool isCursorVisible() const; //cache v

        std::vector<int> getPosition() const; //non-cache v

        std::vector<int> getClientAreaPosition() const; //non-cache v

        std::vector<uint> getSize() const; //non-cache v

        std::vector<uint> getRatio() const; //non-cache v

        const std::string &getTitle() const;//cache v

        std::vector<uint> getMaximumSize() const;//non-cache v

        std::vector<uint> getMinimumSize() const;//non-cache v

        int getGeometryState() const; //non-cache v

        bool isFullscreenEnabled() const; //non-cache v

        int getMaximizationState() const;

        //@todo GLXContext

        std::shared_ptr<dengine::events::mouse::MouseState> getMouseState() const;

        std::shared_ptr<dengine::events::keyboard::KeyboardState> getKeyboardState() const;

        std::shared_ptr<dengine::events::window::WindowState> getWindowState() const;

        ~WindowManagerX();//
    };
}

#endif //DENGINE_WINDOWMANAGERX_H
