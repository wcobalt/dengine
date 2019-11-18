//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>
#include <memory>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

namespace dengine {
    class Component;
    class TransformComponent;
    class Initializer;
}

#include "DObject.h"
#include "Coreutils/ID.h"
#include "Coreutils/Messages.h"

namespace dengine {
    class GameObject : public DObject {
    private:
        std::vector<std::shared_ptr<Component>> components;

        std::shared_ptr<GameObject> parent;
        std::vector<std::shared_ptr<GameObject>> children;
    public:
        GameObject();

        GameObject(const Initializer& initializer);

        GameObject(std::shared_ptr<TransformComponent> transform);

        GameObject(const Initializer& initializer, std::shared_ptr<TransformComponent> transform);

        void addComponent(std::shared_ptr<Component> component);

        template<typename T>
        void removeComponent();

        void removeComponent(std::shared_ptr<Component> component);

        static void instantiate(std::shared_ptr<GameObject> instance);

        void instantiateChild(std::shared_ptr<GameObject> instance);

        static void destroy(std::shared_ptr<GameObject> instance);

        void destroyChild(std::shared_ptr<GameObject> instance);

        void removeAllChildren();

        std::shared_ptr<GameObject> getParent() const;

        std::vector<std::shared_ptr<GameObject>> getChildren() const;

        template<typename T>
        std::shared_ptr<T> getComponent() const;

        std::vector<std::shared_ptr<Component>> getAllComponents() const;

        void sendMessage(GameObjectMessage message);

        ID getId();
    };
}

#endif //DENGINE_GAMEOBJECT_H
