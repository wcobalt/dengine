#include <GL/glx.h>
#include <X11/Xlib.h>
#include <string>
#include <vector>
#include <memory>

//
// Created by wcobalt on 15.09.18.
//

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H

#include "../Events/EventsData.h"
#include "../Geometry/vectors.h"
#include "../Geometry/dimensions.h"

namespace dengine::windowaccessors {
    using namespace events;
    using namespace dengine::geometry;

    class WindowAccessor {
    public:
        const int NOT_FIXED_SIZE = -1;

        //@todo add defualt constructors

        virtual void setVisible(bool isVisible) = 0;

        virtual void setDecorated(bool isDecorated) = 0;

        virtual void setWindowPosition(int x, int y) = 0;

        virtual void setWindowPosition(vec2i position) = 0;

        virtual void setSize(uint width, uint height) = 0;

        virtual void setSize(dim2i size) = 0;

        virtual void setWindowTitle(const std::string &title) = 0;

        virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;

        virtual void setMaximumSize(dim2i size) = 0;

        virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;

        virtual void setMinimumSize(dim2i size) = 0;

        virtual void setFullScreenEnabled(bool isEnabled) = 0;

        virtual bool isVisible() = 0;

        virtual bool isDecorated() = 0;

        virtual vec2i getWindowPosition() const = 0;

        virtual vec2i getClientAreaPosition() const = 0;

        virtual dim2i getSize() const = 0;

        virtual const std::string &getWindowTitle() const = 0;

        virtual dim2i getMaximumSize() const = 0;

        virtual dim2i getMinimumSize() const = 0;

        virtual bool isFullScreenEnabled() const = 0;

        virtual std::shared_ptr<const EventsData> checkEvents() = 0;

        virtual void destroy() = 0;

        virtual ~WindowAccessor() = 0;
    };
}

#endif //DENGINE_WINDOWACCESSOR_H
