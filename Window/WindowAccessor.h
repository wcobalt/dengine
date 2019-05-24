//
// Created by wcobalt on 15.09.18.
//

#include <string>
#include <memory>
#include <vector>

#ifndef DENGINE_WINDOWACCESSOR_H
#define DENGINE_WINDOWACCESSOR_H

namespace dengine::events {
    class EventsData;
}

#include "../DObject.h"

namespace dengine::window {
    class WindowAccessor : public DObject {
    public:
        const int NOT_FIXED_SIZE = -1;

        virtual void setVisible(bool isVisible) = 0;

        virtual void setDecorated(bool isDecorated) = 0;

        virtual void setCursorVisible(bool isVisible) = 0;

        virtual void setWindowPosition(int x, int y) = 0;

        virtual void setSize(uint width, uint height) = 0;

        //@todo hideToTray, icons set

        virtual void setWindowTitle(const std::string &title) = 0;

        virtual void setMaximumSize(uint maximumWidth, uint maximumHeight) = 0;

        virtual void setMinimumSize(uint minimumWidth, uint minimumHeight) = 0;

        virtual void setFullscreenEnabled(bool isEnabled) = 0;

        virtual bool isVisible() const = 0;

        virtual bool isDecorated() const = 0;

        virtual bool isCursorVisible() const = 0;

        virtual std::vector<int> getWindowPosition() const = 0;

        virtual std::vector<int> getClientAreaPosition() const = 0;

        virtual std::vector<uint> getSize() const = 0;

        virtual const std::string &getWindowTitle() const = 0;

        virtual std::vector<uint> getMaximumSize() const = 0;

        virtual std::vector<uint> getMinimumSize() const = 0;

        virtual bool isFullscreenEnabled() const = 0;

        virtual std::shared_ptr<const dengine::events::EventsData> checkEvents() = 0;

        virtual void destroy() = 0;

        virtual ~WindowAccessor() = 0;
    };
}

#endif //DENGINE_WINDOWACCESSOR_H
