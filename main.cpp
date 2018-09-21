#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"

//@TODO x11*, windows(later), and macos(later) support

int main() {
    WindowAccessor* accessor = new WindowAccessorX();

    Dengine* engine = new Dengine(0, 0, 800, 600, "Test window",
                                  new WindowManager(accessor));

    engine->setFPS(2);
    engine->start();

    return 0;
}