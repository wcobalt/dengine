//
// Created by wcobalt on 11/17/19.
//
#include <memory>
#include "Coreutils/Messages/Message.h"

#ifndef DENGINE_BASESCENEBEHAVIOR_H
#define DENGINE_BASESCENEBEHAVIOR_H

namespace dengine {
    class Scene;
}

namespace dengine {
    class SceneBehavior {
    public:
        virtual void onSceneLoad(const Message &message, std::shared_ptr<Scene> scene);

        virtual void onSceneUnload(const Message &message, std::shared_ptr<Scene> scene);

        virtual void onGameEnd(const Message &message, std::shared_ptr<Scene> scene);
    };
}

#endif //DENGINE_BASESCENEBEHAVIOR_H
