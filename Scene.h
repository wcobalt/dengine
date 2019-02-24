//
// Created by wcobalt on 19.09.18.
//

#include <string>
#include <vector>

#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

#include "GameObject.h"

class Scene {
private:
    const std::string& id;
    std::vector<GameObject&> instances;
    const unsigned int BASE_ID = 1000000;
    unsigned int currentID;
    unsigned int width, height;
public:
    Scene(const std::string& id);
    Scene(const std::string& id, unsigned int width, unsigned int height);
    void placeInstance(GameObject& instance);
    void placeInstance(GameObject& instance, float x, float y);
    unsigned int getUniqueGameObjectID();
    const std::string& getID() const;
    //@todo destructors everywhere
};


#endif //DENGINE_SCENE_H
