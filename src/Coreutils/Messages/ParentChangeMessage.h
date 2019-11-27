//
// Created by wcobalt on 11/22/19.
//
#include <memory>

#ifndef DENGINE_PARENTCHANGEMESSAGE_H
#define DENGINE_PARENTCHANGEMESSAGE_H

namespace dengine {
    class GameObject;
}

#include "Message.h"

namespace dengine {
    class ParentChangeMessage : public Message {
    private:
        std::shared_ptr<GameObject> previousParent, newParent;
    public:
        ParentChangeMessage(std::shared_ptr<GameObject> previousParent, std::shared_ptr<GameObject> newParent);

        ParentChangeMessage(std::shared_ptr<GameObject> previousParent, std::shared_ptr<GameObject> newParent,
                                    time_type sendingTime);

        std::shared_ptr<GameObject> getPreviousParent() const {
            return previousParent;
        }

        std::shared_ptr<GameObject> getNewParent() const {
            return newParent;
        }
    };
}

#endif //DENGINE_PARENTCHANGEMESSAGE_H
