#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"

//@TODO x11*, windows(later), and macos(later) support

int main() {
    Dengine engine;

    WindowAccessor* accessor = new WindowAccessorX();

    engine.setWindowManager(new WindowManager(accessor));

    engine.start();

    return 0;
}