//
// Created by wcobalt on 11/22/19.
//
#include <memory>

#ifndef DENGINE_PARENTCHANGEMESSAGE_H
#define DENGINE_PARENTCHANGEMESSAGE_H

namespace dengine {
    class GameObject;
}

#include "ComponentMessage.h"

namespace dengine {
    class ParentChangeMessage : public ComponentMessage {
    private:
        GameObject& newParent;
        GameObject* previousParent;
    public:
        ParentChangeMessage(GameObject *previousParent, GameObject &newParent);

        ParentChangeMessage(GameObject *previousParent, GameObject &newParent,
                            time_type sendingTime);

        GameObject * getPreviousParent() const {
            return previousParent;
        }

        GameObject & getNewParent() const {
            return newParent;
        }

        void handle(Component &component) const override;
    };
}

#endif //DENGINE_PARENTCHANGEMESSAGE_H