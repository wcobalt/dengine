//
// Created by wcobalt on 11/17/19.
//

#ifndef DENGINE_SCENEBEHAVIOR_H
#define DENGINE_SCENEBEHAVIOR_H

#include "DObject.h"

namespace dengine {
    class SceneBehavior : public DObject {
    public:
        virtual void onSceneLoad() = 0;

        virtual void onSceneUnload() = 0;

        virtual void onGameEnd() = 0;
    };
}

#endif //DENGINE_SCENEBEHAVIOR_H
