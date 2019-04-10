//
// Created by wcobalt on 19.09.18.
//
#include <string>
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
    using namespace dengine;
    using std::shared_ptr;

    class Component : public DObject {
    public:
        virtual void componentLoad(DengineAccessor dengineAccessor, shared_ptr<GameObject> instance) = 0;

        virtual void componentUnload(DengineAccessor dengineAccessor) = 0;

        virtual void update(DengineAccessor dengineAccessor) = 0;

        virtual void instanceCreate(DengineAccessor dengineAccessor) = 0;

        virtual void instanceDestroy(DengineAccessor dengineAccessor) = 0;

        virtual void sceneUnload(DengineAccessor dengineAccessor) = 0;

        virtual void setEnabled(bool isEnabled) = 0;

        virtual bool isEnabled() const = 0;

        virtual shared_ptr<GameObject> getBoundInstance() const = 0;

        //@todo make mechanism for pause-exceptions (object which still be calculated when game paused)
    };
}

#endif //DENGINE_COMPONENT_H
