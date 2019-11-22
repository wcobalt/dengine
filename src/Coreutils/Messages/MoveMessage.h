//
// Created by wcobalt on 11/22/19.
//
#include <memory>

#ifndef DENGINE_MOVEMESSAGE_H
#define DENGINE_MOVEMESSAGE_H

namespace dengine {
    class GameObject;
}

#include "Message.h"

namespace dengine {
    class MoveMessage : public Message {
    private:
        std::shared_ptr<GameObject> previousParent;
    public:
        MoveMessage(std::shared_ptr<GameObject> previousParent);

        MoveMessage(std::shared_ptr<GameObject> previousParent, time_type sendingTime);

        std::shared_ptr<GameObject> getExParent() const {
            return previousParent;
        }
    };
}

#endif //DENGINE_MOVEMESSAGE_H
