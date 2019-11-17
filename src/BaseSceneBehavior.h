//
// Created by wcobalt on 11/17/19.
//

#ifndef DENGINE_BASESCENEBEHAVIOR_H
#define DENGINE_BASESCENEBEHAVIOR_H

#include "SceneBehavior.h"

namespace dengine {
    class BaseSceneBehavior : public SceneBehavior {
    public:
        void onSceneLoad() override;

        void onSceneUnload() override;

        void onGameEnd() override;
    };
}

#endif //DENGINE_BASESCENEBEHAVIOR_H
