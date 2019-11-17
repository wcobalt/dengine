//
// Created by wcobalt on 19.09.18.
//

#include <memory>

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

#include "../DObject.h"

namespace dengine {
    class GameObject;
    class EventsState;
}

namespace dengine {
    class Component : public DObject {
    public:
        virtual void onComponentLoad() = 0;

        virtual void onComponentUnload() = 0;

        virtual void onUpdate(std::shared_ptr<EventsState> eventsState) = 0;

        virtual void onInstanceDestroy() = 0;

        virtual void onSceneUnload() = 0;

        virtual void onGameEnd() = 0;

        virtual void setEnabled(bool isEnabled) = 0;

        virtual bool isEnabled() const = 0;

        virtual std::shared_ptr<GameObject> getBoundInstance() const = 0;
    };
}

#endif //DENGINE_COMPONENT_H
