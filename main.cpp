#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"

//@TODO x11*, windows forms(later) support

int main() {
    WindowAccessor* accessor = new WindowAccessorX();

    Dengine* engine = new Dengine(0, 0, 400, 200, "Test window",
                                  *(new WindowManager(*accessor)));

    engine->setFPS(60);

    Scene* mainScene = new Scene("MainScene", 400, 400);

    engine->addScene(*mainScene);
    engine->loadScene("MainScene");

    engine->run();

    return 0;
}