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
        std::vector<std::shared_ptr<dengine::Component>> components;

        std::shared_ptr<dengine::GameObject> parent;
        std::vector<std::shared_ptr<dengine::GameObject>> children;

        void safelyRemoveComponent(std::vector<std::shared_ptr<dengine::Component>>::iterator it);
        void removeComponent(std::vector<std::shared_ptr<dengine::Component>>::iterator it);
        void removeChild(std::vector<std::shared_ptr<dengine::GameObject>>::iterator it);

        void initParent();
    public:
        GameObject();
        GameObject(std::shared_ptr<dengine::TransformComponent> transform);

        void addComponent(std::shared_ptr<dengine::Component> component);

        template <class T>
        void addComponent();

        template <class T>
        void removeComponent();

        void removeComponent(std::shared_ptr<dengine::Component> component);

        void addChild(std::shared_ptr<dengine::GameObject> instance);

        void removeChild(std::shared_ptr<dengine::GameObject> instance);

        void removeAllChildren();

        std::shared_ptr<dengine::GameObject> getParent() const;

        std::vector<std::shared_ptr<dengine::GameObject>> getChildren() const;

        template <class T>
        std::shared_ptr<T> getComponent() const;

        std::vector<std::shared_ptr<dengine::Component>> getAllComponents() const;

        void create(const dengine::DengineAccessor& dengineAccessor);
        void destroy(const dengine::DengineAccessor& dengineAccessor, bool isSceneUnloading);
        void update(const dengine::DengineAccessor& dengineAccessor);
    };
}

#endif //DENGINE_GAMEOBJECT_H
