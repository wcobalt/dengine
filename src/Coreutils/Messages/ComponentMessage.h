//
// Created by wcobalt on 11/22/19.
//
#include <chrono>

#ifndef DENGINE_MESSAGE_H
#define DENGINE_MESSAGE_H

#include "../../Components/Component.h"

namespace dengine {
    class ComponentMessage : public DObject {
    protected:
        using time_type = std::chrono::system_clock::time_point;
    private:
        time_type sendingTime;
        Component::MessageType messageType;
    public:
        ComponentMessage(Component::MessageType messageType);

        ComponentMessage(Component::MessageType messageType, time_type sendingTime);

        virtual time_type getSendingTime() const {
            return sendingTime;
        }

        virtual Component::MessageType getMessageType() const {
            return messageType;
        }
    };
}

#endif //DENGINE_MESSAGE_H
