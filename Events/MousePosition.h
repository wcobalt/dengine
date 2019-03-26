//
// Created by wcobalt on 21.09.18.
//

#ifndef DENGINE_MOUSEPOSITION_H
#define DENGINE_MOUSEPOSITION_H

namespace dengine::events {
    class MousePosition {
    private:
        long rootMouseX, rootMouseY;
        long windowMouseX, windowMouseY;
    public:
        MousePosition(long rootMouseX, long rootMouseY, long windowMouseX, long windowMouseY);

        long getRootMouseX() const;

        long getRootMouseY() const;

        long getWindowMouseX() const;

        long getWindowMouseY() const;
    };
}

#endif //DENGINE_MOUSEPOSITION_H
