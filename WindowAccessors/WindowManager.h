//
// Created by wcobalt on 16.09.18.
//

#include <memory>

#ifndef DENGINE_WINDOWMANAGER_H
#define DENGINE_WINDOWMANAGER_H

#include "WindowAccessor.h"

namespace dengine::windowaccessors {
    class WindowManager {
    private:
        std::shared_ptr<WindowAccessor> windowAccessor;
    public:
        WindowManager(std::shared_ptr<WindowAccessor> windowAccessor);

        std::shared_ptr<WindowAccessor> getWindowAccessor();
    };
}

#endif //DENGINE_WINDOWMANAGER_H
