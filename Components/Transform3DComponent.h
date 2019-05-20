//
// Created by wcobalt on 2/23/19.
//

#ifndef DENGINE_TRANSFORM3DCOMPONENT_H
#define DENGINE_TRANSFORM3DCOMPONENT_H

#include <memory>

#include "DefaultComponent.h"
#include "../GameObject.h"
#include "../Geometry/vectors.h"

namespace dengine::components {
    class Transform3DComponent : public DefaultComponent {
    private:
        dengine::geometry::vec3f position;
        dengine::geometry::vec3f rotation;
        dengine::geometry::vec3f scale;
    public:
        Transform3DComponent();
        Transform3DComponent(dengine::geometry::vec3f position);
        Transform3DComponent(float x, float y, float z);
        Transform3DComponent(dengine::geometry::vec3f position, dengine::geometry::vec3f rotation,
                             dengine::geometry::vec3f scale);

        void setPosition(float x, float y, float z);
        void setPosition(dengine::geometry::vec3f vec);
        void setRotation(float x, float y, float z);
        void setRotation(dengine::geometry::vec3f vec);
        void setScale(float x, float y, float z);
        void setScale(dengine::geometry::vec3f vec);

        dengine::geometry::vec3f getPosition() const;
        dengine::geometry::vec3f getRotation() const;
        dengine::geometry::vec3f getScale() const;

        double getDistanceTo(std::shared_ptr<dengine::GameObject> instance) const;
        double getDistanceTo(dengine::geometry::vec3f position) const;

        template <class T>
        std::shared_ptr<dengine::GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORM3DCOMPONENT_H
