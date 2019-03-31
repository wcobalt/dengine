//
// Created by wcobalt on 19.09.18.
//
#include <string>
#include <memory>

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

#include "../GameObject.h"

namespace dengine::components {
    using std::shared_ptr;

    class Component {
    public:
        virtual void componentLoad(shared_ptr<GameObject> instance) = 0;

        virtual void componentUnload() = 0;

        virtual void update() = 0;

        virtual void instanceCreate() = 0;

        virtual void instanceDestroy() = 0;

        virtual void sceneUnload() = 0;

        virtual void setEnabled(bool isEnabled) = 0;

        virtual bool isEnabled() const = 0;

        virtual shared_ptr<GameObject> getBoundInstance() const = 0;

        //@todo make mechanism for pause-exceptions (object which still be calculated when game paused)
    };
}

#endif //DENGINE_COMPONENT_H
