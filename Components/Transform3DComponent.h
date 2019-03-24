//
// Created by wcobalt on 2/23/19.
//

#ifndef DENGINE_TRANSFORMCOMPONENT_H
#define DENGINE_TRANSFORMCOMPONENT_H

#include "Component.h"
#include "../Geometry/vector3f.h"

namespace dengine::components {
    using namespace dengine::geometry;

    class Transform3DComponent : public Component {
    public:
        Transform3DComponent();

        void componentLoad();

        void componentUnload();

        void update();

        void instanceCreated();

        void instanceDestroyed();

        void setPosition(float x, float y, float z);
        void setPosition(vector3f vec);
        void setRotation(float x, float y, float z);
        void setRotation(vector3f vec);
        void setScale(float x, float y, float z);
        void setScale(vector3f vec);

        vector3f getPosition();
        vector3f getRotation();
        vector3f getScale();
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
