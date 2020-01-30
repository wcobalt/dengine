//
// Created by wcobalt on 19.09.18.
//
#include <vector>
#include <string>
#include <memory>
#include <optional>

#ifndef DENGINE_GAMEOBJECT_H
#define DENGINE_GAMEOBJECT_H

namespace dengine {
    class Component;
    class TransformComponent;
    class Initializer;
    class ComponentsManager;
}

#include "DObject.h"
#include "Coreutils/ID.h"
#include "Math/vectors.h"
#include "Coreutils/Messages/DirectChildrenChangeMessage.h"

namespace dengine {
    class GameObject final : public DObject {
    private:
        std::unique_ptr<ComponentsManager> componentsManager;

        GameObject* parent;

        //it is guaranteed that the Nth element in children will be the Nth element in childrenFrontend
        std::vector<std::unique_ptr<GameObject>> children;
        std::vector<GameObject*> childrenFrontend;//@todo is it good?

        ID id = IDUtils::NO_ID;
    public:
        using iterator = decltype(childrenFrontend)::iterator;
        using const_iterator = decltype(childrenFrontend)::const_iterator;
    private:
        void destroyChild(decltype(children)::const_iterator iterator);

        void initialize(bool doAddTransform);

        decltype(children)::const_iterator findChild(GameObject &instance) const;

        void addChildWithoutInstantiation(std::unique_ptr<GameObject> instance);

        void notifyAboutAdditionWithoutInstantiation(GameObject &instance,
                                                     const DirectChildrenChangeMessage::ChildChangeType &childrenChangeType,
                                                     GameObject *previousParent);

        GameObject & instantiateNew(const Initializer& initializer, std::optional<vec3f> position);

        GameObject & instantiateByCloning(const GameObject& pattern, std::optional<vec3f> position);

        GameObject&
        recursivelyInstantiate(const GameObject &pattern, GameObject &parent, const std::optional<vec3f> &position,
                               const std::optional<vec3f> &origin);

        void notifyAboutInstantiation(bool doPropagateToChildren);
    public:
        enum class EventType {
            UPDATE, SCENE_UNLOAD, GAME_END
        };

        static GameObject & instantiate(const Initializer& initializer);

        static GameObject & instantiate(const Initializer& initializer, float x, float y, float z);

        static GameObject & instantiate(const Initializer& initializer, const vec3f& position);

        static GameObject & instantiate(const GameObject &instance);

        static GameObject & instantiate(const GameObject &instance, float x, float y, float z);

        static GameObject & instantiate(const GameObject &instance, const vec3f &position);

        GameObject & instantiateChild(const Initializer& initializer);

        GameObject & instantiateChild(const Initializer& initializer, float x, float y, float z);

        GameObject & instantiateChild(const Initializer& initializer, const vec3f &position);

        GameObject & instantiateChild(const GameObject &instance);

        GameObject & instantiateChild(const GameObject &instance, float x, float y, float z);

        GameObject & instantiateChild(const GameObject &instance, const vec3f &position);

        static void move(GameObject &instance);

        void moveToChildren(GameObject &instance);

        void destroy();

        void destroyChild(GameObject &instance);

        void destroyAllChildren();

        GameObject & getParent() const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        void handleExternalEvent(EventType eventType);

        static GameObject & getRoot();

        ComponentsManager & getComponentsManager() const;

        ID getId() const;

        //@todo things which are returned by reference can be reassigned (copy can be made). consider this (CompMan&TrComp are fixed)

        bool operator==(const GameObject& gameObject) const;

        bool operator!=(const GameObject& gameObject) const;
    };
}

#endif //DENGINE_GAMEOBJECT_H
