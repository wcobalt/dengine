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
    class MoveMessage;
}

#include "../Coreutils/Messages/MessageType.h"
#include "../DObject.h"
#include "../Coreutils/Messages/Message.h"

namespace dengine {
    class Component : public DObject, public std::enable_shared_from_this<Component> {
    private:
        bool mIsEnabled;
    protected:
        std::shared_ptr<GameObject> gameObject;
    public:
        Component(std::shared_ptr<GameObject> gameObject);

        void onInstanceCreate(const Message &message);

        void onComponentLoad(const Message &message);

        void onComponentUnload(const Message &message);

        void onUpdate(const Message &message);

        void onInstanceDestroy(const Message &message);

        void onSceneUnload(const Message &message);

        void onGameEnd(const Message &message);

        void onDirectChildrenChange(const DirectChildrenChangeMessage &message);

        void onParentChange(const ParentChangeMessage &message);

        void setEnabled(bool isEnabled);

        void sendMessage(ComponentMessageType messageType, const Message &message);

        bool isEnabled() const;

        std::shared_ptr<GameObject> getGameObject() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
