#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"

//@TODO x11*, windows(later), and macos(later) support

int main() {
    WindowAccessorX* accessorX = new WindowAccessorX();

    accessorX->initialize(0, 0, 0, 0, new GLint{});

    return 0;
}