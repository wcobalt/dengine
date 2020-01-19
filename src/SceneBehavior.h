//
// Created by wcobalt on 11/17/19.
//
#include <memory>
#include "Coreutils/Messages/ComponentMessage.h"

#ifndef DENGINE_BASESCENEBEHAVIOR_H
#define DENGINE_BASESCENEBEHAVIOR_H

namespace dengine {
    class Scene;
}

namespace dengine {
    class SceneBehavior {
    public:
        virtual void onSceneLoad(Scene &scene);

        virtual void onSceneUnload(Scene &scene);

        virtual void onGameEnd(Scene &scene);
    };
}

#endif //DENGINE_BASESCENEBEHAVIOR_H
