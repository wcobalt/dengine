//
// Created by wcobalt on 1/23/20.
//

#ifndef DENGINE_COMPONENTMESSAGES_H
#define DENGINE_COMPONENTMESSAGES_H

/**
 * THIS FILE CONTAINS SEVERAL CLASSES FOR THE FOLLOWING REASON:
 *
 * ALL OF THEM CONTAIN BASIC LOGIC RELATED TO CALLING OF NEEDED COMPONENTS' METHOD (VISITOR PATTERN).
 * WHEN NEW LOGIC IS ADDED TO THEM, CHANGING CLASS MUST BE EXCLUDED TO SEPARATE FILE.
 * */

#include "ComponentMessage.h"

namespace dengine {
    class InstanceCreateMessage : public ComponentMessage {
    public:
        InstanceCreateMessage();

        InstanceCreateMessage(const ComponentMessage::time_type &sendingTime);

        void handle(Component &component) const override;
    };

    class InstanceDestroyMessage : public ComponentMessage {
    public:
        InstanceDestroyMessage();

        InstanceDestroyMessage(const time_type &sendingTime);

        void handle(Component &component) const override;
    };

    class ComponentLoadMessage : public ComponentMessage {
    public:
        ComponentLoadMessage();

        ComponentLoadMessage(const time_type &sendingTime);

        void handle(Component &component) const override;
    };

    class ComponentUnloadMessage : public ComponentMessage {
    public:
        ComponentUnloadMessage();

        ComponentUnloadMessage(const time_type &sendingTime);

        void handle(Component &component) const override;
    };

    class UpdateMessage : public ComponentMessage {
    public:
        UpdateMessage();

        UpdateMessage(const time_type &sendingTime);

        void handle(Component &component) const override;
    };

    class SceneUnloadMessage : public ComponentMessage {
    public:
        SceneUnloadMessage();

        SceneUnloadMessage(const time_type &sendingTime);

        void handle(Component &component) const override;
    };

    class GameEndMessage : public ComponentMessage {
    public:
        GameEndMessage();

        GameEndMessage(const time_type &sendingTime);

        void handle(Component &component) const override;
    };
}

#endif //DENGINE_COMPONENTMESSAGES_H
