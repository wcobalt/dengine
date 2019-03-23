#include <iostream>
#include "WindowAccessors/WindowAccessorX.h"
#include <string>
#include "Dengine.h"
#include <memory>

//@TODO windows forms(later) support

using namespace dengine;
using namespace dengine::windowaccessors;

int main() {//memory safe
    std::shared_ptr<WindowAccessor> accessor(new WindowAccessorX(0, 0, 400, 200, "Test window"));
    std::shared_ptr<WindowManager> windowManager(new WindowManager(accessor));
    std::shared_ptr<Dengine> dengine(new Dengine(windowManager));

    dengine->setFPS(60);

    std::shared_ptr<Scene> mainScene(new Scene("MainScene", 400, 400));

    dengine->addScene(mainScene);
    dengine->loadScene("MainScene");

    dengine->run();

    return 0;
}