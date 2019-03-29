//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <vector>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

#include "GameObject.h"

namespace dengine {
    class Scene {
    private:
        vector<shared_ptr<Entry<GameObject>>> instances;

        ID nextInstanceId;

        ID getUniqueGameObjectId();

        shared_ptr<GameObject> getInstance(ID id);

        ID getID(shared_ptr<GameObject> instance);
    public:
        Scene();

        void placeInstance(shared_ptr<GameObject> instance);

        void placeInstance(shared_ptr<GameObject> instance, float x, float y);
        void placeInstance(shared_ptr<GameObject> instance, float x, float y, float z);

        void destroyInstance(shared_ptr<GameObject> instance);

        template<class T>
        vector<shared_ptr<GameObject>> getInstances();

        template<class T>
        vector<shared_ptr<GameObject>> getNearestInstance();
    };
}

#endif //DENGINE_SCENE_H
