//
// Created by wcobalt on 2/23/19.
//

#ifndef DENGINE_TRANSFORMCOMPONENT_H
#define DENGINE_TRANSFORMCOMPONENT_H

#include "Component.h"
#include "../Geometry/vectors.h"

namespace dengine::components {
    using namespace dengine::geometry;

    class Transform3DComponent : public Component {
    private:
        vec3f position;
        vec3f rotation;
        vec3f scale;
    public:
        Transform3DComponent();

        void componentLoad();

        void componentUnload();

        void update();

        void instanceCreated();

        void instanceDestroyed();

        void setPosition(float x, float y, float z);
        void setPosition(vec3f vec);
        void setRotation(float x, float y, float z);
        void setRotation(vec3f vec);
        void setScale(float x, float y, float z);
        void setScale(vec3f vec);

        vec3f getPosition();
        vec3f getRotation();
        vec3f getScale();
    };
}

#endif //DENGINE_TRANSFORMCOMPONENT_H
