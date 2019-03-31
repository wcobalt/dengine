//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <map>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

#include "GameObject.h"
#include "Coreutils/Entry.h"
#include "ScenesManager.h"

namespace dengine {
    using namespace dengine::coreutils;

    using std::shared_ptr;

    class Scene {
    public:
        const float ROOT_GAME_OBJECT_X = 0;
        const float ROOT_GAME_OBJECT_Y = 0;
        const float ROOT_GAME_OBJECT_Z = 0;
    private:
        shared_ptr<GameObject> root;
    public:
        Scene();

        void update();

        virtual void sceneLoad();
        virtual void sceneUnload();

        void placeInstance(shared_ptr<GameObject> instance);

        void placeInstance(shared_ptr<GameObject> instance, float x, float y);
        void placeInstance(shared_ptr<GameObject> instance, float x, float y, float z);

        void destroyInstance(shared_ptr<GameObject> instance);

        void clean();

        template <class T>
        vector<shared_ptr<GameObject>> getInstances() const;

        shared_ptr<GameObject> getRoot() const;
    };
}

#endif //DENGINE_SCENE_H
