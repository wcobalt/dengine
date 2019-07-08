//
// Created by wcobalt on 6/1/19.
//

#ifndef DENGINE_UNABLETOATTACHGLXCONTEXTTOWINDOW_H
#define DENGINE_UNABLETOATTACHGLXCONTEXTTOWINDOW_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine::platform::window::x::exceptions {
    class UnableToAttachGLXContextToWindow : public dengine::exceptions::DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_UNABLETOATTACHGLXCONTEXTTOWINDOW_H
