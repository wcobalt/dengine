//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <map>
#include <memory>
#include <vector>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

namespace dengine {
    class GameObject;
}

#include "DObject.h"

namespace dengine {
    class Scene : public DObject {
    private:
        std::shared_ptr<GameObject> root;

        void deleteInstance(std::shared_ptr<GameObject> instance, bool isSceneUnloading);
    public:
        Scene();

        void placeInstance(std::shared_ptr<GameObject> instance);

        void placeInstance(std::shared_ptr<GameObject> instance, float x, float y);

        void placeInstance(std::shared_ptr<GameObject> instance, float x, float y, float z);

        void destroyInstance(std::shared_ptr<GameObject> instance);

        void update();

        void create();

        void destroy();

        void endGame();

        template<typename T>
        std::vector<std::shared_ptr<GameObject>> getInstances() const; //@todo to filter or something

        std::shared_ptr<GameObject> getRoot() const;
    };
}

#endif //DENGINE_SCENE_H
