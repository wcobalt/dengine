//
// Created by wcobalt on 16.09.18.
//

#include <memory>

#ifndef DENGINE_WINDOWMANAGER_H
#define DENGINE_WINDOWMANAGER_H

#include "WindowAccessor.h"

namespace dengine::windowaccessors {
    using std::shared_ptr;

    class WindowManager {
    private:
        shared_ptr<WindowAccessor> windowAccessor;

        shared_ptr<const EventsData> eventsData;
    public:
        WindowManager(shared_ptr<WindowAccessor> windowAccessor);

        void checkEvents();

        shared_ptr<WindowAccessor> getWindowAccessor();

        shared_ptr<const EventsData> getEventsData() const;
    };
}

#endif //DENGINE_WINDOWMANAGER_H
