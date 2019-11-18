//
// Created by wcobalt on 11/17/19.
//
#include <memory>

#ifndef DENGINE_BASESCENEBEHAVIOR_H
#define DENGINE_BASESCENEBEHAVIOR_H

namespace dengine {
    class Scene;
}

namespace dengine {
    class SceneBehavior {
    public:
        void onSceneLoad(Scene &scene);

        void onSceneUnload(Scene &scene);

        void onGameEnd(Scene &scene);
    };
}

#endif //DENGINE_BASESCENEBEHAVIOR_H
