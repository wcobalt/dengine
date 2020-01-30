//
// Created by wcobalt on 11/22/19.
//
#include <memory>

#ifndef DENGINE_CHILDRENCHANGEMESSAGE_H
#define DENGINE_CHILDRENCHANGEMESSAGE_H

namespace dengine {
    class GameObject;
}

#include "ComponentMessage.h"

namespace dengine {
    class DirectChildrenChangeMessage : public ComponentMessage {
    public:
        enum class ChildChangeType {
            DESTRUCTION, INSTANTIATION, MOVE_FROM, MOVE_TO
        };
    private:
        GameObject& changedChild;

        ChildChangeType childChangeType;
    public:
        DirectChildrenChangeMessage(ChildChangeType childChangeType,
                                    GameObject &changedChild);

        DirectChildrenChangeMessage(ChildChangeType childChangeType,
                                    GameObject &changedChild, time_type sendingTime);

        ChildChangeType getChildChangeType() const {
            return childChangeType;
        }

        GameObject & getChangedChild() const {
            return changedChild;
        }

        void handle(Component &component) const override;
    };
}

#endif //DENGINE_CHILDRENCHANGEMESSAGE_H