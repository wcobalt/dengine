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
    MousePosition();
    MousePosition(int rootMouseX, int rootMouseY, int windowMouseX, int windowMouseY);

    int getRootMouseX();
    int getRootMouseY();
    int getWindowMouseX();
    int getWindowMouseY();

    void setRootMousePosition(int rootMouseX, int rootMouseY);
    void setWindowMousePosition(int windowMouseX, int windowMouseY);
};


#endif //DENGINE_MOUSEPOSITION_H
