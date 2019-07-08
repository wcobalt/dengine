//
// Created by wcobalt on 2/23/19.
//

#include <memory>

#ifndef DENGINE_TRANSFORM3DCOMPONENT_H
#define DENGINE_TRANSFORM3DCOMPONENT_H

namespace dengine {
    class GameObject;
}

#include "DefaultComponent.h"
#include "../Geometry/vectors.h"

namespace dengine::components {
    class TransformComponent : public DefaultComponent {
    private:
        dengine::geometry::vec3f position;
        dengine::geometry::vec3f rotation;
        dengine::geometry::vec3f scale;
    public:
        TransformComponent();
        TransformComponent(const dengine::geometry::vec3f& position);
        TransformComponent(float x, float y, float z);
        TransformComponent(const dengine::geometry::vec3f& position, const dengine::geometry::vec3f& rotation,
                             const dengine::geometry::vec3f& scale);

        void setPosition(float x, float y, float z);
        void setPosition(const dengine::geometry::vec3f& vec);
        void setRotation(float x, float y, float z);
        void setRotation(const dengine::geometry::vec3f& vec);
        void setScale(float x, float y, float z);
        void setScale(const dengine::geometry::vec3f& vec);

        dengine::geometry::vec3f getPosition() const;
        dengine::geometry::vec3f getRotation() const;
        dengine::geometry::vec3f getScale() const;

        double getDistanceTo(std::shared_ptr<dengine::GameObject> instance) const;
        double getDistanceTo(const dengine::geometry::vec3f& position) const;

        template <class T>
        std::shared_ptr<dengine::GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORM3DCOMPONENT_H
