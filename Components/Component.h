//
// Created by wcobalt on 19.09.18.
//
#include <string>

#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

namespace dengine::components {
    class Component {
    private:
        bool mIsEnabled;
    public:
        Component();

        virtual void componentLoad() = 0;

        virtual void componentUnload() = 0;

        virtual void update() = 0;

        virtual void instanceCreated() = 0;

        virtual void instanceDestroyed() = 0;

        void setEnabled(bool isEnabled);

        bool isEnabled() const;

        //@todo make mechanism for pause-exceptions (object which still be calculated when game paused)
    };
}

#endif //DENGINE_COMPONENT_H
