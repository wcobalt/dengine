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
        const std::string &id;
        std::vector<GameObject &> instances;
        const uint BASE_ID = 1000000;
        uint currentID;
        uint width, height;
    public:
        Scene(const std::string &id);

        Scene(const std::string &id, uint width, uint height);

        void placeInstance(GameObject &instance);

        void placeInstance(GameObject &instance, float x, float y);

        uint getUniqueGameObjectID();

        const std::string &getID() const;
    };
}

#endif //DENGINE_SCENE_H
