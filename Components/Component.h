//
// Created by wcobalt on 19.09.18.
//

#include <memory>

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

#include "../DObject.h"
#include "../DengineAccessor.h"
#include "../GameObject.h"

namespace dengine {
    class GameObject;
}

namespace dengine::components {
    class Component : public DObject {
    public:
        virtual void componentLoad(dengine::DengineAccessor dengineAccessor, std::shared_ptr<dengine::GameObject> instance) = 0;

        virtual void componentUnload(dengine::DengineAccessor dengineAccessor) = 0;

        virtual void update(dengine::DengineAccessor dengineAccessor) = 0;

        virtual void instanceCreate(dengine::DengineAccessor dengineAccessor) = 0;

        virtual void instanceDestroy(dengine::DengineAccessor dengineAccessor) = 0;

        virtual void sceneUnload(dengine::DengineAccessor dengineAccessor) = 0;

        virtual void setEnabled(bool isEnabled) = 0;

        virtual bool isEnabled() const = 0;

        virtual std::shared_ptr<dengine::GameObject> getBoundInstance() const = 0;

        //@todo make mechanism for pause-exceptions (object which still be calculated when game paused)
    };
}

#endif //DENGINE_COMPONENT_H
