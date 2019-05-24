//
// Created by wcobalt on 3/30/19.
//

#include <memory>

#ifndef DENGINE_DEFAULTCOMPONENT_H
#define DENGINE_DEFAULTCOMPONENT_H

namespace dengine {
    class GameObject;
    class DengineAccessor;
}

#include "Component.h"

namespace dengine::components {
    class DefaultComponent : public Component {
    private:
        bool mIsEnabled;

        std::shared_ptr<dengine::GameObject> boundInstance;
    public:
        DefaultComponent();

        virtual void componentLoad(const dengine::DengineAccessor& dengineAccessor, std::shared_ptr<dengine::GameObject> instance);

        virtual void componentUnload(const dengine::DengineAccessor& dengineAccessor);

        virtual void update(const dengine::DengineAccessor& dengineAccessor);

        virtual void instanceCreate(const dengine::DengineAccessor& dengineAccessor);

        virtual void instanceDestroy(const dengine::DengineAccessor& dengineAccessor);

        virtual void sceneUnload(const dengine::DengineAccessor& dengineAccessor);

        virtual void setEnabled(bool isEnabled);

        virtual bool isEnabled() const;

        virtual std::shared_ptr<dengine::GameObject> getBoundInstance() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
