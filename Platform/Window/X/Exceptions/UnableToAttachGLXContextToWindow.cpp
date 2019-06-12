//
// Created by wcobalt on 6/1/19.
//

#include "UnableToAttachGLXContextToWindow.h"

using namespace dengine::platform::window::x::exceptions;

const char* UnableToAttachGLXContextToWindow::what() const noexcept {
    return "Unable to attach created GLXContext to X Window";
}