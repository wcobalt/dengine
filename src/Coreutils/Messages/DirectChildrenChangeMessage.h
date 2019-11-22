//
// Created by wcobalt on 11/22/19.
//
#include <memory>

#ifndef DENGINE_CHILDRENCHANGEMESSAGE_H
#define DENGINE_CHILDRENCHANGEMESSAGE_H

namespace dengine {
    class GameObject;
}

#include "Message.h"

namespace dengine {
    class DirectChildrenChangeMessage : public Message {
    public:
        enum class ChildChangeType {
            DESTROY, INSTANCE, MOVE_FROM, MOVE_TO
        };
    private:
        std::shared_ptr<GameObject> changedChild;

        ChildChangeType childChangeType;
    public:
        DirectChildrenChangeMessage(ChildChangeType childChangeType, std::shared_ptr<GameObject> changedChild);

        DirectChildrenChangeMessage(ChildChangeType childChangeType, std::shared_ptr<GameObject> changedChild, time_type sendingTime);

        ChildChangeType getChildChangeType() const {
            return childChangeType;
        }
    };
}

#endif //DENGINE_CHILDRENCHANGEMESSAGE_H
