//
// Created by wcobalt on 21.09.18.
//

#ifndef DENGINE_MOUSEPOSITION_H
#define DENGINE_MOUSEPOSITION_H

#include "../Geometry/vectors.h"
#include "../DObject.h"

namespace dengine::events {
    //@todo think about Dobject
    //@todo make WindowAccessor independent from vec2 and dimension (make MousePosition for Dengine, return for user with vec2)
    class MousePosition : public DObject {
    private:
        dengine::geometry::vec2i rootMousePosition, windowMousePosition;
    public:
        MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY);

        dengine::geometry::vec2i getRootMousePosition() const;

        dengine::geometry::vec2i getWindowMousePosition() const;
    };
}

#endif //DENGINE_MOUSEPOSITION_H
