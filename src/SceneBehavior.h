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
        virtual void onSceneLoad(std::shared_ptr<Scene> scene);

        virtual void onSceneUnload(std::shared_ptr<Scene> scene);

        virtual void onGameEnd(std::shared_ptr<Scene> scene);
    };
}

#endif //DENGINE_BASESCENEBEHAVIOR_H
