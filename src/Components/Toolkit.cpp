//
// Created by wcobalt on 1/31/20.
//

#include "Toolkit.h"
#include "../Dengine.h"
#include "../ScenesManager.h"
#include "../Scene.h"

using namespace dengine;

Toolkit::Toolkit(Component &component) : component(component) {}

Scene &Toolkit::getCurrentScene() const {
    return Dengine::get().getScenesManager().getCurrentScene();
}

SpacesManager &Toolkit::getSpacesManager() const {
    return getCurrentScene().getSpacesManager();
}

Component &Toolkit::getComponent() const {
    return component;
}
