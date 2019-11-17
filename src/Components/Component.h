//
// Created by wcobalt on 19.09.18.
//

#include <memory>

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

#include "../DObject.h"

namespace dengine {
    class GameObject;
    class DengineAccessor;
}

namespace dengine {
    class Component : public DObject {
    public:
        virtual void componentLoad(const DengineAccessor& dengineAccessor, std::shared_ptr<GameObject> instance) = 0;

        virtual void componentUnload(const DengineAccessor& dengineAccessor) = 0;

        virtual void update(const DengineAccessor& dengineAccessor) = 0;

        virtual void instanceCreate(const DengineAccessor& dengineAccessor) = 0;

        virtual void instanceDestroy(const DengineAccessor& dengineAccessor) = 0;

        virtual void sceneUnload(const DengineAccessor& dengineAccessor) = 0;

        virtual void setEnabled(bool isEnabled) = 0;

        virtual bool isEnabled() const = 0;

        virtual std::shared_ptr<GameObject> getBoundInstance() const = 0;
    };
}

#endif //DENGINE_COMPONENT_H
