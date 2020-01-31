//
// Created by wcobalt on 1/31/20.
//

#ifndef DENGINE_TOOLKIT_H
#define DENGINE_TOOLKIT_H

#include "../DObject.h"

namespace dengine {
    class Scene;
    class Component;
    class SpacesManager;
}

namespace dengine {
    class Toolkit : public DObject {
    private:
        Component& component;
    public:
        explicit Toolkit(Component& component);

        virtual Scene& getCurrentScene() const;

        virtual SpacesManager& getSpacesManager() const;

        virtual Component& getComponent() const;
    };
}

#endif //DENGINE_TOOLKIT_H
