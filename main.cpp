#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"

//@TODO x11*, windows(later), and macos(later) support

int main() {
    Dengine engine;

    engine.setWindowManager();

    return 0;
}