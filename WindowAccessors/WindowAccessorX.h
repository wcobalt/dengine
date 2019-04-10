#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSORX_H
#define DENGINE_WINDOWACCESSORX_H

#include "WindowAccessor.h"
#include "../Events/EventsData.h"

namespace dengine::windowaccessors {
    using namespace dengine::events;

    using std::shared_ptr;

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

    class WindowAccessorX : public WindowAccessor {
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

        const std::string& title;

        PropertyData getProperty(const char *propertyName, long offset, long size, Window window) const;

        void setMinimumAndMaximumSize(uint maximumWidth, uint maximumHeight,
                                      uint minimumWidth, uint minimumHeight);

    public:
        WindowAccessorX(int x, int y, uint width, uint height, const std::string& title);
        WindowAccessorX(vec2i position, dim2i size, const std::string &title);

        void setVisible(bool isVisible);

        void setDecorated(bool isDecorated);

        void setCursorVisible(bool isVisible);

        void setWindowPosition(int x, int y);

        void setWindowPosition(vec2i position);

        void setSize(uint width, uint height);

        void setSize(dim2i size);

        void setWindowTitle(const std::string& title);

        void setMaximumSize(uint maximumWidth, uint maximumHeight);

        void setMaximumSize(dim2i size);

        void setMinimumSize(uint minimumWidth, uint minimumHeight);

        void setMinimumSize(dim2i size);

        void setFullScreenEnabled(bool isEnabled);

        bool isVisible() const;

        bool isDecorated() const;

        bool isCursorVisible() const;

        vec2i getWindowPosition() const;

        vec2i getClientAreaPosition() const;

        dim2i getSize() const;

        const std::string &getWindowTitle() const;

        dim2i getMaximumSize() const;

        dim2i getMinimumSize() const;

        bool isFullScreenEnabled() const;

        shared_ptr<const EventsData> checkEvents();

        ~WindowAccessorX();

        void destroy();
    };
}

#endif //DENGINE_WINDOWACCESSORX_H
