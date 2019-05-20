//
// Created by wcobalt on 15.09.18.
//

//@todo dynamic WindowAccessor linking

#include <string>
#include <memory>

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H

#include "../Events/EventsData.h"
#include "../Geometry/dimensions.h"
#include "../Geometry/vectors.h"
#include "../DObject.h"

namespace dengine::window {
    class WindowAccessor : public DObject {
    public:
        const int NOT_FIXED_SIZE = -1;

        //@todo add default constructors

        virtual void setVisible(bool isVisible) = 0;

        virtual void setDecorated(bool isDecorated) = 0;

        virtual void setCursorVisible(bool isVisible) = 0;

        virtual void setWindowPosition(int x, int y) = 0;

        virtual void setWindowPosition(dengine::geometry::vec2i position) = 0;

        virtual void setSize(uint width, uint height) = 0;

        virtual void setSize(dengine::geometry::dim2i size) = 0;

        virtual void setWindowTitle(const std::string &title) = 0;

        virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;

        virtual void setMaximumSize(dengine::geometry::dim2i size) = 0;

        virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;

        virtual void setMinimumSize(dengine::geometry::dim2i size) = 0;

        virtual void setFullScreenEnabled(bool isEnabled) = 0;

        virtual bool isVisible() const = 0;

        virtual bool isDecorated() const = 0;

        virtual bool isCursorVisible() const = 0;

        virtual dengine::geometry::vec2i getWindowPosition() const = 0;

        virtual dengine::geometry::vec2i getClientAreaPosition() const = 0;

        virtual dengine::geometry::dim2i getSize() const = 0;

        virtual const std::string &getWindowTitle() const = 0;

        virtual dengine::geometry::dim2i getMaximumSize() const = 0;

        virtual dengine::geometry::dim2i getMinimumSize() const = 0;

        virtual bool isFullScreenEnabled() const = 0;

        virtual std::shared_ptr<const dengine::events::EventsData> checkEvents() = 0;

        virtual void destroy() = 0;

        virtual ~WindowAccessor() = 0;
    };
}

#endif //DENGINE_WINDOWACCESSOR_H
