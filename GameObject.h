//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>
#include <memory>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

#include "DObject.h"
#include "Components/Component.h"
#include "Components/Transform3DComponent.h"

namespace dengine::components {
    class Component;
}

namespace dengine {
    class GameObject : public DObject {
    private:
        std::vector<std::shared_ptr<dengine::components::Component>> components;

        std::shared_ptr<dengine::GameObject> parent;
        std::vector<std::shared_ptr<dengine::GameObject>> children;

        void safelyRemoveComponent(std::vector<std::shared_ptr<dengine::components::Component>>::iterator it);
        void removeComponent(std::vector<std::shared_ptr<dengine::components::Component>>::iterator it);
        void removeChild(std::vector<std::shared_ptr<dengine::GameObject>>::iterator it);

        void initParent();
    public:
        GameObject();
        GameObject(std::shared_ptr<dengine::components::Transform3DComponent> transform);

        void addComponent(std::shared_ptr<dengine::components::Component> component);

        template<class T>
        void addComponent();

        template <class T>
        void removeComponent();

        void removeComponent(std::shared_ptr<dengine::components::Component> component);

        void addChild(std::shared_ptr<dengine::GameObject> instance);

        void removeChild(std::shared_ptr<dengine::GameObject> instance);

        void removeAllChildren();

        std::shared_ptr<dengine::GameObject> getParent() const;

        std::vector<std::shared_ptr<dengine::GameObject>> getChildren() const;

        template <class T>
        std::shared_ptr<T> getComponent() const;

        std::vector<std::shared_ptr<dengine::components::Component>> getAllComponents() const;

        void create(dengine::DengineAccessor dengineAccessor);
        void destroy(dengine::DengineAccessor dengineAccessor, bool isSceneUnloading);
        void update(dengine::DengineAccessor dengineAccessor);
    };
}

#endif //DENGINE_GAMEOBJECT_H
