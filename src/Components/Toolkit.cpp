//
// Created by wcobalt on 1/31/20.
//

#include "Toolkit.h"
#include "../Dengine.h"
#include "../ScenesManager.h"

using namespace dengine;

Scene &Toolkit::getCurrentScene() const {
    return Dengine::get().getScenesManager().getCurrentScene();
}
