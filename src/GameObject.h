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
#include "Exceptions/GameObjectException.h"

namespace dengine {
    class GameObject : public DObject, public std::enable_shared_from_this<GameObject> {
    private:
        std::vector<std::shared_ptr<Component>> components;

        std::shared_ptr<GameObject> parent;
        std::vector<std::shared_ptr<GameObject>> children;

        std::shared_ptr<Initializer> initializer;
        std::shared_ptr<TransformComponent> userDefinedTransform;

        ID id;

        using const_component_iterator = decltype(components)::const_iterator;

        void detachComponent(const_component_iterator iterator);

        void destroyChild(decltype(children)::const_iterator iterator);

        void checkComponentAttachment(std::shared_ptr<Component> component);

        const_component_iterator findComponent(std::shared_ptr<Component> component) const;

        void initialize();

        void sendMessageToComponents(ComponentMessage message);
    public:
        using iterator = decltype(children)::iterator;

        using const_iterator = decltype(children)::const_iterator;

        GameObject();

        GameObject(std::shared_ptr<Initializer> initializer);

        GameObject(std::shared_ptr<TransformComponent> transform);

        GameObject(std::shared_ptr<Initializer> initializer, std::shared_ptr<TransformComponent> transform);

        void attachComponent(std::shared_ptr<Component> component);

        template<typename T>
        void detachComponent() {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (std::dynamic_pointer_cast<T>(*it)) {
                    detachComponent(it);

                    return;
                }
            }

            throw GameObjectException("Cannot detach component of this type, because it is not attached yet");
        }

        void detachComponent(std::shared_ptr<Component> component);

        void detachAllComponents();

        static void instantiate(std::shared_ptr<GameObject> instance);

        void instantiateChild(std::shared_ptr<GameObject> instance);

        static void destroy(std::shared_ptr<GameObject> instance);

        void destroyChild(std::shared_ptr<GameObject> instance);

        void destroyAllChildren();

        std::shared_ptr<GameObject> getParent() const;

        std::vector<std::shared_ptr<GameObject>> getChildren() const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (auto result = std::dynamic_pointer_cast<T>(*it)) {
                    return result;
                }
            }

            throw GameObjectException("Cannot return component of this type, because is is not attached yet.");
        }

        std::vector<std::shared_ptr<Component>> getAllComponents() const;

        void sendMessage(GameObjectMessage message);

        ID getId() const;
    };
}

#endif //DENGINE_GAMEOBJECT_H
