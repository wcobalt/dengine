//
// Created by wcobalt on 11/25/19.
//
#include <memory>
#include <vector>

#ifndef DENGINE_COMPONENTSMANAGER_H
#define DENGINE_COMPONENTSMANAGER_H

namespace dengine {
    class ComponentMessage;
    class GameObject;
}

#include "DObject.h"
#include "Exceptions/ComponentException.h"
#include "Components/Component.h"
#include "Components/Transform/TransformComponent.h"

namespace dengine {
    class ComponentsManager : public DObject {
    private:
        mutable std::vector<std::unique_ptr<Component>> components;
        std::vector<Component*> componentsFrontend;//@fixme that's not cool

        GameObject& gameObject;

        TransformComponent* transformComponent = nullptr;
    public:
        using const_iterator = decltype(componentsFrontend)::const_iterator;
        using iterator = decltype(componentsFrontend)::iterator;
    private:
        void detachComponent(decltype(components)::const_iterator iterator);

        void checkComponentAttachment(const Component &component);

        decltype(components)::const_iterator findComponent(const Component &component) const;

        void attachComponentWithoutNotification(std::unique_ptr<Component> component);
    public:
        explicit ComponentsManager(GameObject &gameObject);

        ComponentsManager& operator=(const ComponentsManager& componentsManager) = delete;

        void attachComponent(std::unique_ptr<Component> component);

        template<typename T, typename std::enable_if<!std::is_same<T, TransformComponent>::value, std::nullptr_t>::type = nullptr>
        void detachComponent() {
            for (auto it = components.begin(); it != components.end(); it++) {
                Component& component = **it;
                if (typeid(component).hash_code() == typeid(T).hash_code()) {
                    detachComponent(it);

                    return;
                }
            }

            throw ComponentException("Cannot detach component of this type, because it is not attached yet");
        }

        void detachComponent(const Component &component);

        void detachAllComponents();

        template<typename T>
        T & getComponent() const {
            for (auto & component : components) {
                //@fixme use hashtable when hash is typeid().hash_code() (but how to get Transform and keep compsFrontend?)
                if (auto result = std::dynamic_pointer_cast<T>(component)) {
                    return *result;
                }
            }

            throw ComponentException("Cannot return component of this type, because is is not attached yet.");
        }

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        TransformComponent& getTransformComponent() const;

        std::unique_ptr<ComponentsManager> clone(GameObject& gameObject) const;

        void spreadMessage(const ComponentMessage &message);
    };
}

#endif //DENGINE_COMPONENTSMANAGER_H
