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
    public:
        explicit ComponentsManager(GameObject &gameObject);

        ComponentsManager& operator=(const ComponentsManager& componentsManager) = delete;

        void attachComponent(std::unique_ptr<Component> component);

        //probably it needs perfect forwarding
        /*
         * if T is TransformComponent pass true in private method attach(unique, bool). In that function if bool is true
         * then component is automatically considered as TransformComp otherwise - it checks for "Transformity"
         * */
        template<typename T, typename ...Types>
        void attachComponent(Types ...args) {
            attachComponent(std::make_unique<T>(gameObject, args...));
        }

        template<typename T, typename std::enable_if<!std::is_same<T, TransformComponent>::value, std::nullptr_t>::type = nullptr>
        void detachComponent() {
            size_t tHash = typeid(T).hash_code();

            for (auto it = components.begin(); it != components.end(); it++) {
                Component& component = **it;

                if (typeid(component).hash_code() == tHash) {
                    detachComponent(it);

                    return;
                }
            }

            throw ComponentException("Cannot detach component of this type (" + std::string(typeid(T).name())
                                     + "), because it is not attached yet");
        }

        void detachComponent(const Component &component);

        void detachAllComponents();

        template<typename T>
        T & getComponent() const {
            for (auto & component : components) {
                //@fixme use hashtable when hash is typeid().hash_code() (but how to get Transform and keep compsFrontend?)
                if (auto result = dynamic_cast<T&>(*component)) {
                    return result;
                }
            }

            throw ComponentException("Cannot return component of this type (" + std::string(typeid(T).name())
                                     + "), because is is not attached yet.");
        }

        template<typename T>
        bool isComponentAttached() const {
            size_t tHash = typeid(T).hash_code();

            for (auto& component : components) {
                Component& componentReference = *component;

                if (typeid(componentReference).hash_code() == tHash)
                    return true;
            }

            return false;
        }

        bool isComponentAttached(const Component& component) const;

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
