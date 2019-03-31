//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_DEFAULTCOMPONENT_H
#define DENGINE_DEFAULTCOMPONENT_H

#include "Component.h"

namespace dengine::components {
    class DefaultComponent : public Component {
    private:
        bool mIsEnabled;

        shared_ptr<GameObject> boundInstance;
    public:
        DefaultComponent();

        virtual void componentLoad(shared_ptr<GameObject> instance);

        virtual void componentUnload();

        virtual void update();

        virtual void instanceCreate();

        virtual void instanceDestroy();

        virtual void sceneUnload();

        virtual void setEnabled(bool isEnabled);

        virtual bool isEnabled() const;

        virtual shared_ptr<GameObject> getBoundInstance() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
