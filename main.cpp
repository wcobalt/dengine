#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"
#include <memory>

//@TODO windows forms(later) support

int main() {//memory safe
    std::shared_ptr<WindowAccessor> accessor(new WindowAccessorX());
    std::shared_ptr<WindowManager> windowManager(new WindowManager(*accessor));
    std::shared_ptr<Dengine> engine(new Dengine(0, 0, 400, 200, "Test window", *windowManager));

    engine->setFPS(60);

    std::shared_ptr<Scene> mainScene(new Scene("MainScene", 400, 400));

    engine->addScene(*mainScene);
    engine->loadScene("MainScene");

    engine->run();

    return 0;
}