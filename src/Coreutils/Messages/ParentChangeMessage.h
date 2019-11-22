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
        std::shared_ptr<GameObject> previousParent;
    public:
        ParentChangeMessage(std::shared_ptr<GameObject> previousParent);

        ParentChangeMessage(std::shared_ptr<GameObject> previousParent, time_type sendingTime);

        std::shared_ptr<GameObject> getExParent() const {
            return previousParent;
        }
    };
}

#endif //DENGINE_PARENTCHANGEMESSAGE_H
