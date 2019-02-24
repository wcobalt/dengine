//
// Created by wcobalt on 2/23/19.
//

#ifndef DENGINE_TRANSFORMCOMPONENT_H
#define DENGINE_TRANSFORMCOMPONENT_H

#include "Component.h"

class TransformComponent : public Component {
public:
    TransformComponent(const std::string& id);
    void sceneLoad();
    void sceneUnload();
    void componentLoad();
    void componentUnload();
    void update();
    void create();
    void destroy();
    void draw();
    void setPosition(float x, float y);
};


#endif //DENGINE_TRANSFORMCOMPONENT_H
