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
    class ComponentsManager;
}

#include "DObject.h"
#include "Coreutils/ID.h"
#include "Exceptions/GameObjectException.h"
#include "Math/vectors.h"
#include "Coreutils/Messages/ComponentMessage.h"
#include "Coreutils/Messages/DirectChildrenChangeMessage.h"

namespace dengine {
    class GameObject : public DObject, public std::enable_shared_from_this<GameObject> {
    private:
        std::shared_ptr<ComponentsManager> componentsManager;

        std::shared_ptr<GameObject> parent;
        std::vector<std::shared_ptr<GameObject>> children;

        std::shared_ptr<Initializer> initializer;
        std::shared_ptr<TransformComponent> userDefinedTransform;

        ID id;

        void destroyChild(decltype(children)::const_iterator iterator);

        void initialize();

        void instantiateAsChild(std::shared_ptr<GameObject> instance);

        decltype(children)::const_iterator findChild(std::shared_ptr<GameObject> instance) const;

        void addChildWithoutInstantiation(std::shared_ptr<GameObject> instance);

        void noticeAboutAddingWithoutInstantiation(std::shared_ptr<GameObject> instance,
                                                   const DirectChildrenChangeMessage::ChildChangeType &childrenChangeType,
                                                   std::shared_ptr<GameObject> previousParent);
    public:
        enum class EventType {
            UPDATE, SCENE_UNLOAD, GAME_END
        };

        using iterator = decltype(children)::iterator;

        using const_iterator = decltype(children)::const_iterator;

        GameObject();

        GameObject(std::shared_ptr<Initializer> initializer);

        GameObject(std::shared_ptr<TransformComponent> transform);

        GameObject(std::shared_ptr<Initializer> initializer, std::shared_ptr<TransformComponent> transform);

        static void instantiate(std::shared_ptr<GameObject> instance);

        static void instantiate(std::shared_ptr<GameObject> instance, float x, float y, float z);

        static void instantiate(std::shared_ptr<GameObject> instance, const vec3f &position);

        void instantiateChild(std::shared_ptr<GameObject> instance);

        void instantiateChild(std::shared_ptr<GameObject> instance, float x, float y, float z);

        void instantiateChild(std::shared_ptr<GameObject> instance, vec3f position);

        static void move(std::shared_ptr<GameObject> instance);

        void moveToChildren(std::shared_ptr<GameObject> instance);

        static void destroy(std::shared_ptr<GameObject> instance);

        void destroy();

        void destroyChild(std::shared_ptr<GameObject> instance);

        void destroyAllChildren();

        std::shared_ptr<GameObject> getParent() const;

        std::vector<std::shared_ptr<GameObject>> getAllChildren() const;

        iterator begin();

        iterator end();

        const_iterator begin() const;

        const_iterator end() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        void handleExternalEvent(EventType eventType);

        static std::shared_ptr<GameObject> getRoot();

        std::shared_ptr<GameObject> clone() const;

        std::shared_ptr<ComponentsManager> getComponentsManager() const;

        ID getId() const;
    };
}

#endif //DENGINE_GAMEOBJECT_H
