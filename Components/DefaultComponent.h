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

        virtual void componentLoad(DengineAccessor dengineAccessor, shared_ptr<GameObject> instance);

        virtual void componentUnload(DengineAccessor dengineAccessor);

        virtual void update(DengineAccessor dengineAccessor);

        virtual void instanceCreate(DengineAccessor dengineAccessor);

        virtual void instanceDestroy(DengineAccessor dengineAccessor);

        virtual void sceneUnload(DengineAccessor dengineAccessor);

        virtual void setEnabled(bool isEnabled);

        virtual bool isEnabled() const;

        virtual shared_ptr<GameObject> getBoundInstance() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
