//
// Created by wcobalt on 19.09.18.
//

#include "Components/Component.h"
#include <vector>
#include <string>
#include "ID.h"

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H


class GameObject {
private:
    ID* id;
    const std::vector<const Component *const> components;
    GameObject *parent;
    std::vector<const GameObject*> children;
public:
    //constructors
    const std::vector<const Component *const> *const getAllComponents();
    const std::vector<const Component *const> *const getComponentsByName(std::string name);
    const std::vector<const Component *const> *const getComponentsByGroup(std::string group);
    void addComponent(Component *component);
    void setParent(GameObject *parent);
    void addChild(std::vector<GameObject*> children);
    GameObject *getParent();
    const std::vector<GameObject*> getChildren();
    ID *getID();
};


#endif //DENGINE_GAMEOBJECT_H
