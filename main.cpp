#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"

//@TODO x11*, windows(later), and macos(later) support

int main() {
    WindowAccessor* accessor = new WindowAccessorX();

    Dengine* engine = new Dengine(0, 0, 400, 200, "Test window",
                                  new WindowManager(accessor));

    engine->setFPS(30);
    engine->start();

    return 0;
}