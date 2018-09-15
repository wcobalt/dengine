#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>

//@TODO x11*, windows(later), and macos(later) support

int main() {
    WindowAccessorX* accessorX = new WindowAccessorX();

    GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    accessorX->initialize(0, 0, 600, 400, att, ExposureMask | KeyPressMask, "A title");

    return 0;
}