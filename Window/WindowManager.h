//
// Created by wcobalt on 16.09.18.
//

#include <memory>

#ifndef DENGINE_WINDOWMANAGER_H
#define DENGINE_WINDOWMANAGER_H

#include "WindowAccessor.h"
#include "../Events/EventsData.h"
#include "../DObject.h"

namespace dengine::window {
    class WindowManager : public DObject {
    private:
        std::shared_ptr<WindowAccessor> windowAccessor;

        std::shared_ptr<const dengine::events::EventsData> eventsData;
    public:
        WindowManager(std::shared_ptr<WindowAccessor> windowAccessor);

        void checkEvents();

        std::shared_ptr<WindowAccessor> getWindowAccessor();

        std::shared_ptr<const dengine::events::EventsData> getEventsData() const;
    };
}

#endif //DENGINE_WINDOWMANAGER_H
