//
// Created by wcobalt on 3/30/19.
//

#include <memory>

#ifndef DENGINE_DEFAULTCOMPONENT_H
#define DENGINE_DEFAULTCOMPONENT_H

namespace dengine {
    class GameObject;
    class Events;
    class DirectChildrenChangeMessage;
    class ParentChangeMessage;
    class ComponentMessage;
    class InstanceCreateMessage;
    class InstanceDestroyMessage;
    class ComponentLoadMessage;
    class ComponentUnloadMessage;
    class UpdateMessage;
    class SceneUnloadMessage;
    class GameEndMessage;
    class Scene;
    class Toolkit;
}

#include "../DObject.h"

namespace dengine {
    class Component : public DObject {
    private:
        bool mIsEnabled;

        std::unique_ptr<Toolkit> toolkit;
    protected:
        GameObject& gameObject;
    public:
        //safe component has to be non-copyable (because of gameObject reference)
        Component& operator=(const Component& component) = delete;

        Component(GameObject &gameObject);

        void onInstanceCreate(const InstanceCreateMessage &message);

        void onComponentLoad(const ComponentLoadMessage &message);

        void onComponentUnload(const ComponentUnloadMessage &message);

        void onUpdate(const UpdateMessage &message);

        void onInstanceDestroy(const InstanceDestroyMessage &message);

        void onSceneUnload(const SceneUnloadMessage &message);

        void onGameEnd(const GameEndMessage &message);

        void onDirectChildrenChange(const DirectChildrenChangeMessage &message);

        void onParentChange(const ParentChangeMessage &message);

        void setEnabled(bool isEnabled);

        void sendMessage(const ComponentMessage &message);

        bool isEnabled() const;

        GameObject & getGameObject() const;

        std::unique_ptr<Component> clone(GameObject& gameObject) const;

        Toolkit& getToolkit();
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
