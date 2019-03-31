//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_TRANSFORM2DCOMPONENT_H
#define DENGINE_TRANSFORM2DCOMPONENT_H

#include "Transform3DComponent.h"

namespace dengine::components {
    using namespace dengine::geometry;

    class Transform2DComponent : public Transform3DComponent {
    public:
        Transform2DComponent();
        Transform2DComponent(vec2f position);
        Transform2DComponent(float x, float y);
        Transform2DComponent(vec2f position, vec2f rotation, vec2f scale);

        void setPosition(float x, float y);

        void setRotation(float x, float y);

        void setScale(float x, float y);

        vec2f getPosition() const;
        vec2f getRotation() const;
        vec2f getScale() const;

        double getDistanceTo(vec2f position) const;
    };
}

#endif //DENGINE_TRANSFORM2DCOMPONENT_H
