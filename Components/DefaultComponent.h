//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_DEFAULTCOMPONENT_H
#define DENGINE_DEFAULTCOMPONENT_H

#include <memory>

#include "Component.h"
#include "../GameObject.h"
#include "../DengineAccessor.h"

namespace dengine::components {
    class DefaultComponent : public Component {
    private:
        bool mIsEnabled;

        std::shared_ptr<dengine::GameObject> boundInstance;
    public:
        DefaultComponent();

        virtual void componentLoad(dengine::DengineAccessor dengineAccessor, std::shared_ptr<dengine::GameObject> instance);

        virtual void componentUnload(dengine::DengineAccessor dengineAccessor);

        virtual void update(dengine::DengineAccessor dengineAccessor);

        virtual void instanceCreate(dengine::DengineAccessor dengineAccessor);

        virtual void instanceDestroy(dengine::DengineAccessor dengineAccessor);

        virtual void sceneUnload(dengine::DengineAccessor dengineAccessor);

        virtual void setEnabled(bool isEnabled);

        virtual bool isEnabled() const;

        virtual std::shared_ptr<dengine::GameObject> getBoundInstance() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
