//
// Created by wcobalt on 3/30/19.
//

#include <memory>

#ifndef DENGINE_DEFAULTCOMPONENT_H
#define DENGINE_DEFAULTCOMPONENT_H

namespace dengine {
    class GameObject;
    class EventsState;
}

#include "../Coreutils/Messages.h"
#include "../DObject.h"

namespace dengine {
    class Component : public DObject, public std::enable_shared_from_this<Component> {
    private:
        bool mIsEnabled;
    protected:
        std::shared_ptr<GameObject> gameObject;
    public:
        Component(std::shared_ptr<GameObject> gameObject);

        void onInstanceCreate();

        void onComponentLoad();

        void onComponentUnload();

        void onUpdate();

        void onInstanceDestroy();

        void onSceneUnload();

        void onGameEnd();

        void setEnabled(bool isEnabled);

        void sendMessage(ComponentMessage message);

        bool isEnabled() const;

        std::shared_ptr<GameObject> getGameObject() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
