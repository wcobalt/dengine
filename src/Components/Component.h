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

namespace dengine {
    class Component {
    private:
        bool mIsEnabled;
    protected:
        std::shared_ptr<GameObject> gameObject;
    public:
        Component(std::shared_ptr<GameObject> gameObject);

        void onComponentLoad();

        void onComponentUnload();

        void onUpdate(std::shared_ptr<EventsState> eventsState);

        void onInstanceDestroy();

        void onSceneUnload();

        void onGameEnd();

        void setEnabled(bool isEnabled);

        bool isEnabled() const;

        std::shared_ptr<GameObject> getGameObject() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
