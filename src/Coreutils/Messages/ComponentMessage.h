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
    public:
        enum class Type {
            INSTANCE_CREATE, INSTANCE_DESTROY, COMPONENT_LOAD, COMPONENT_UNLOAD, UPDATE, SCENE_UNLOAD, GAME_END,
            DIRECT_CHILDREN_CHANGE, PARENT_CHANGE
        };
    private:
        time_type sendingTime;
        Type messageType;
    public:
        ComponentMessage(Type messageType);

        ComponentMessage(Type messageType, time_type sendingTime);

        virtual time_type getSendingTime() const {
            return sendingTime;
        }

        virtual Type getMessageType() const {
            return messageType;
        }

        virtual void handle(Component& component) const = 0;
    };
}

#endif //DENGINE_MESSAGE_H
