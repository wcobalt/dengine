//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

#include "Components/Component.h"
#include "Dengine.h"

namespace dengine {
    using namespace components;
    using std::vector;
    using std::shared_ptr;

    class GameObject {
    private:
        vector<shared_ptr<Component>> components;
        shared_ptr<GameObject> parent;
        vector<shared_ptr<GameObject>> children;
    public:
        GameObject();

        template<class T>
        void addComponent(shared_ptr<Component> component);

        template<class T>
        void removeComponent();

        void setParent(shared_ptr<GameObject> id);

        void addChild(shared_ptr<GameObject> id);

        void removeChild(shared_ptr<GameObject> id);

        shared_ptr<GameObject> getParent() const;

        vector<shared_ptr<GameObject>> getChildren() const;

        template<class T>
        vector<shared_ptr<Component>> getComponents() const;

        vector<shared_ptr<Component>> getAllComponents() const;
    };
}

#endif //DENGINE_GAMEOBJECT_H
