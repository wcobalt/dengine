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
    using namespace events;

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

        PropertyData getProperty(char *propertyName, long offset, long size, Window window) const;

        void setMinimumAndMaximumSize(uint maximumWidth, uint maximumHeight,
                                      uint minimumWidth, uint minimumHeight);

    public:
        WindowAccessorX(int x, int y, uint width, uint height, const std::string& title);

        void setPosition(int x, int y);

        void setPosition(vec2i position);

        void setSize(uint width, uint height);

        void setSize(vec2i size);

        void setWindowTitle(const std::string& title);

        void setMaximumSize(uint maximumWidth, uint maximumHeight);

        void setMaximumSize(vec2i size);

        void setMinimumSize(uint minimumWidth, uint minimumHeight);

        void setMinimumSize(vec2i size);

        void setFullscreenEnabled(bool isEnabled);

        vec2i getPosition();

        vec2i getRelativeClientAreaPosition();

        vec2i getSize() const;

        const std::string &getWindowTitle() const;

        vec2i getMaximumSize() const;

        vec2i getMinimumSize() const;

        bool isFullscreenEnabled() const;

        std::shared_ptr<const EventsData> checkEvents();

        void destroy();
    };
}

#endif //DENGINE_WINDOWACCESSORX_H
