//
// Created by wcobalt on 3/30/19.
//

#include <memory>

#ifndef DENGINE_DEFAULTCOMPONENT_H
#define DENGINE_DEFAULTCOMPONENT_H

namespace dengine {
    class GameObject;
    class EventsState;
    class DirectChildrenChangeMessage;
    class ParentChangeMessage;
    class ComponentMessage;
}

#include "../DObject.h"

namespace dengine {
    class Component : public DObject, public std::enable_shared_from_this<Component> {
    private:
        bool mIsEnabled;
    protected:
        GameObject& gameObject;
    public:
        enum class MessageType {
            INSTANCE_CREATE, INSTANCE_DESTROY, COMPONENT_LOAD, COMPONENT_UNLOAD, UPDATE, SCENE_UNLOAD, GAME_END,
            DIRECT_CHILDREN_CHANGE, PARENT_CHANGE
        };

        Component(GameObject &gameObject);

        void onInstanceCreate(const ComponentMessage &message);

        void onComponentLoad(const ComponentMessage &message);

        void onComponentUnload(const ComponentMessage &message);

        void onUpdate(const ComponentMessage &message);

        void onInstanceDestroy(const ComponentMessage &message);

        void onSceneUnload(const ComponentMessage &message);

        void onGameEnd(const ComponentMessage &message);

        void onDirectChildrenChange(const DirectChildrenChangeMessage &message);

        void onParentChange(const ParentChangeMessage &message);

        void setEnabled(bool isEnabled);

        void sendMessage(const ComponentMessage &message);

        bool isEnabled() const;

        GameObject & getGameObject() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
