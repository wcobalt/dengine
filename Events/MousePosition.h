//
// Created by wcobalt on 21.09.18.
//

#include "../Geometry/vectors.h"

#ifndef DENGINE_MOUSEPOSITION_H
#define DENGINE_MOUSEPOSITION_H

namespace dengine::events {
    using namespace dengine::geometry;

    class MousePosition {
    private:
        vec2i rootMousePosition, windowMousePosition;
    public:
        MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY);

        vec2i getRootMousePosition() const;

        vec2i getWindowMousePosition() const;
    };
}

#endif //DENGINE_MOUSEPOSITION_H
