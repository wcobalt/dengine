//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>
#include <memory>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

#include "Components/TransformComponent.h"

namespace dengine {
    class Component;
    class TransformComponent;
}

#include "DObject.h"

namespace dengine {
    class GameObject : public DObject {
    private:
        std::vector<std::shared_ptr<Component>> components;

        std::shared_ptr<GameObject> parent;
        std::vector<std::shared_ptr<GameObject>> children;

        void safelyRemoveComponent(std::vector<std::shared_ptr<Component>>::iterator it);
        void removeComponent(std::vector<std::shared_ptr<Component>>::iterator it);
        void removeChild(std::vector<std::shared_ptr<GameObject>>::iterator it);

        void initParent();
    public:
        GameObject();

        GameObject(std::shared_ptr<TransformComponent> transform);

        void addComponent(std::shared_ptr<Component> component);

        template<typename T>
        void addComponent();

        template<typename T>
        void removeComponent();

        void removeComponent(std::shared_ptr<Component> component);

        void addChild(std::shared_ptr<GameObject> instance);

        void removeChild(std::shared_ptr<GameObject> instance);

        void removeAllChildren();

        std::shared_ptr<GameObject> getParent() const;

        std::vector<std::shared_ptr<GameObject>> getChildren() const;

        template<typename T>
        std::shared_ptr<T> getComponent() const;

        std::vector<std::shared_ptr<Component>> getAllComponents() const;

        void create();

        void destroy(bool isSceneUnloading);

        void update();
    };
}

#endif //DENGINE_GAMEOBJECT_H
