//
// Created by wcobalt on 21.09.18.
//

#ifndef DENGINE_MOUSEPOSITION_H
#define DENGINE_MOUSEPOSITION_H

class MousePosition {
private:
    int rootMouseX, rootMouseY;
    int windowMouseX, windowMouseY;
public:
    MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY);

    int getRootMouseX() const;
    int getRootMouseY() const;
    int getWindowMouseX() const;
    int getWindowMouseY() const;
};


#endif //DENGINE_MOUSEPOSITION_H
