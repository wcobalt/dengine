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
    ID id;
    std::vector<Component*> components;
    GameObject* parent;
    std::vector<GameObject*> children;
public:
    std::vector<Component*>* getAllComponents();
    std::vector<Component*>* getComponentsByName(std::string name);
    std::vector<Component*>* getComponentsByGroup(std::string group);
    void addComponent(Component component);
    void setParent(GameObject* parent);
    void addChild(std::vector<GameObject*> children);
    GameObject* getParent();
    std::vector<GameObject*>* getChildren();
    ID* getID();
};


#endif //DENGINE_GAMEOBJECT_H
