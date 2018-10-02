//
// Created by wcobalt on 19.09.18.
//

#include "Components/Component.h"
#include <vector>
#include <string>
#include "IDPattern.h"

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H


class GameObject {
public:
    std::vector<Component> getAllComponents();
    std::vector<Component> getComponentsByID(IDPattern id);
    void addComponent(Component component);
    void setParent(GameObject parent);
    void addChild(std::vector<GameObject> children);
    GameObject getParent();
    std::vector<GameObject> getChildren();
    IDPattern getID();
protected:
    IDPattern id;
};


#endif //DENGINE_GAMEOBJECT_H
