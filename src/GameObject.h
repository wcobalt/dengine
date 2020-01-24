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
    class GameObject final : public DObject, public std::enable_shared_from_this<GameObject> {
    private:
        std::unique_ptr<ComponentsManager> componentsManager;

        GameObject* parent;

        //it is guaranteed that the Nth element in children will be the Nth element in childrenFrontend
        std::vector<std::unique_ptr<GameObject>> children;
        std::vector<GameObject*> childrenFrontend;//@todo is it good?

        std::unique_ptr<TransformComponent> userDefinedTransform;

        ID id = IDUtils::NO_ID;
    public:
        using iterator = decltype(childrenFrontend)::iterator;

        using const_iterator = decltype(childrenFrontend)::const_iterator;
    private:
        void destroyChild(decltype(children)::const_iterator iterator);

        void initialize();

        void instantiateAsChild(std::unique_ptr<GameObject> instance, const Initializer &initializer,
                                std::optional<vec3f> position);

        decltype(children)::const_iterator findChild(GameObject &instance) const;

        void addChildWithoutInstantiation(std::unique_ptr<GameObject> instance);

        void noticeAboutAddingWithoutInstantiation(GameObject &instance,
                                                   const DirectChildrenChangeMessage::ChildChangeType &childrenChangeType,
                                                   GameObject *previousParent);

        void instantiateNew(const Initializer& initializer, std::optional<vec3f> position);

        void instantiateByCloning(GameObject& instance, std::optional<vec3f> position);
    public:
        enum class EventType {
            UPDATE, SCENE_UNLOAD, GAME_END
        };

        GameObject();

        explicit GameObject(std::unique_ptr<TransformComponent> transform);

        static void instantiate(const Initializer& initializer);

        static void instantiate(const Initializer& initializer, float x, float y, float z);

        static void instantiate(const Initializer& initializer, const vec3f& position);

        static void instantiate(GameObject &instance);

        static void instantiate(GameObject &instance, float x, float y, float z);

        static void instantiate(GameObject &instance, const vec3f &position);

        void instantiateChild(const Initializer& initializer);

        void instantiateChild(const Initializer& initializer, float x, float y, float z);

        void instantiateChild(const Initializer& initializer, const vec3f &position);

        void instantiateChild(GameObject &instance);

        void instantiateChild(GameObject &instance, float x, float y, float z);

        void instantiateChild(GameObject &instance, const vec3f &position);

        static void move(GameObject &instance);

        void moveToChildren(GameObject &instance);

        void destroy();

        void destroyChild(GameObject &instance);

        void destroyAllChildren();

        GameObject & getParent() const;

        std::vector<GameObject*> getAllChildren() const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        void handleExternalEvent(EventType eventType);

        static GameObject & getRoot();

        std::unique_ptr<GameObject> clone() const;

        ComponentsManager & getComponentsManager() const;

        ID getId() const;

        bool operator==(const GameObject& gameObject) const;

        bool operator!=(const GameObject& gameObject) const;
    };
}

#endif //DENGINE_GAMEOBJECT_H
