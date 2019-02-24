//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

#include "Components/Component.h"
#include "Dengine.h"

class GameObject {
private:
    const unsigned int id;
    std::vector<Component&> components;
    GameObject* parent;
    std::vector<GameObject&> children;
public:
    GameObject(unsigned int id);

    std::vector<Component&>& getAllComponents() const;
    std::vector<Component&> getComponentsByID(const std::string& name) const;

    void addComponent(Component& component);
    void removeComponent(std::string name);

    void setParent(GameObject& parent);

    void addChild(GameObject& child);
    void removeChild(unsigned int id);

    std::vector<Component&> hui();

    GameObject& getParent() const;
    std::vector<GameObject&> getChildren() const;
    unsigned int getID() const;
};


#endif //DENGINE_GAMEOBJECT_H
