//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

#include "Components/Component.h"
#include "Dengine.h"
#include "Components/Transform3DComponent.h"

namespace dengine {
    using namespace components;

    using std::vector;
    using std::shared_ptr;

    class GameObject {
    private:
        vector<shared_ptr<Component>> components;

        shared_ptr<GameObject> parent;
        vector<shared_ptr<GameObject>> children;

        void removeComponent(vector<shared_ptr<Component>>::iterator it);
    public:
        GameObject(shared_ptr<Transform3DComponent> transform);

        void addComponent(shared_ptr<Component> component);

        template <class T>
        void removeComponent();

        void removeComponent(shared_ptr<Component> component);

        void addChild(shared_ptr<GameObject> instance);

        void removeChild(shared_ptr<GameObject> instance);

        void removeAllChildren();

        shared_ptr<GameObject> getParent() const;

        vector<shared_ptr<GameObject>> getChildren() const;

        template <class T>
        shared_ptr<T> getComponent() const;

        vector<shared_ptr<Component>> getAllComponents() const;
    };
}

#endif //DENGINE_GAMEOBJECT_H
