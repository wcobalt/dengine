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

namespace dengine {
    class ComponentsManager : public DObject {
    private:
        std::vector<std::shared_ptr<Component>> components;
        std::shared_ptr<GameObject> gameObject;

        using const_component_iterator = decltype(components)::const_iterator;

        void detachComponent(const_component_iterator iterator);

        void checkComponentAttachment(std::shared_ptr<Component> component);

        const_component_iterator findComponent(std::shared_ptr<Component> component) const;

    public:
        ComponentsManager(std::shared_ptr<GameObject> gameObject);

        void attachComponent(std::shared_ptr<Component> component);

        template<typename T>
        void detachComponent() {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (std::dynamic_pointer_cast<T>(*it)) {
                    detachComponent(it);

                    return;
                }
            }

            throw ComponentException("Cannot detach component of this type, because it is not attached yet");
        }

        void detachComponent(std::shared_ptr<Component> component);

        void detachAllComponents();

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for (auto it = components.begin(); it != components.end(); it++) {
                if (auto result = std::dynamic_pointer_cast<T>(*it)) {
                    return result;
                }
            }

            throw ComponentException("Cannot return component of this type, because is is not attached yet.");
        }

        std::vector<std::shared_ptr<Component>> getAllComponents() const;

        void spreadMessage(const ComponentMessage &message);
    };
}

#endif //DENGINE_COMPONENTSMANAGER_H
