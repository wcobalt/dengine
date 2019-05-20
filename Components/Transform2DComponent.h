//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_TRANSFORM2DCOMPONENT_H
#define DENGINE_TRANSFORM2DCOMPONENT_H

#include "Transform3DComponent.h"
#include "../Geometry/vectors.h"

namespace dengine::components {
    class Transform2DComponent : public Transform3DComponent {
    public:
        Transform2DComponent();
        //@todo some warning need to be removed
        Transform2DComponent(dengine::geometry::vec2f position);
        Transform2DComponent(float x, float y);
        Transform2DComponent(dengine::geometry::vec2f position,
                             dengine::geometry::vec2f rotation,
                             dengine::geometry::vec2f scale);

        void setPosition(float x, float y);

        void setRotation(float x, float y);

        void setScale(float x, float y);

        dengine::geometry::vec2f getPosition() const;
        dengine::geometry::vec2f getRotation() const;
        dengine::geometry::vec2f getScale() const;

        double getDistanceTo(dengine::geometry::vec2f position) const;
    };
}

#endif //DENGINE_TRANSFORM2DCOMPONENT_H
