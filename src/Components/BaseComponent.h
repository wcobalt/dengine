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

namespace dengine {
    class BaseComponent : public Component {
    private:
        bool mIsEnabled;

        std::shared_ptr<GameObject> boundInstance;
    public:
        BaseComponent() = default;

        virtual void componentLoad(const DengineAccessor& dengineAccessor, std::shared_ptr<GameObject> instance);

        virtual void componentUnload(const DengineAccessor& dengineAccessor);

        virtual void update(const DengineAccessor& dengineAccessor);

        virtual void instanceCreate(const DengineAccessor& dengineAccessor);

        virtual void instanceDestroy(const DengineAccessor& dengineAccessor);

        virtual void sceneUnload(const DengineAccessor& dengineAccessor);

        virtual void setEnabled(bool isEnabled);

        virtual bool isEnabled() const;

        virtual std::shared_ptr<GameObject> getBoundInstance() const;
    };
}

#endif //DENGINE_DEFAULTCOMPONENT_H
