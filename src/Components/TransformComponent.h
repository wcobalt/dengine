//
// Created by wcobalt on 2/23/19.
//

#include <memory>

#ifndef DENGINE_TRANSFORM3DCOMPONENT_H
#define DENGINE_TRANSFORM3DCOMPONENT_H

namespace dengine {
    class GameObject;
}

#include "BaseComponent.h"
#include "../Geometry/vectors.h"

namespace dengine {
    class TransformComponent : public BaseComponent {
    private:
        dengine::vec3f position;
        dengine::vec3f rotation;
        dengine::vec3f scale;
    public:
        TransformComponent();
        TransformComponent(const dengine::vec3f& position);
        TransformComponent(float x, float y, float z);
        TransformComponent(const dengine::vec3f& position, const dengine::vec3f& rotation,
                             const dengine::vec3f& scale);

        void setPosition(float x, float y, float z);
        void setPosition(const dengine::vec3f& vec);
        void setRotation(float x, float y, float z);
        void setRotation(const dengine::vec3f& vec);
        void setScale(float x, float y, float z);
        void setScale(const dengine::vec3f& vec);

        dengine::vec3f getPosition() const;
        dengine::vec3f getRotation() const;
        dengine::vec3f getScale() const;

        double getDistanceTo(std::shared_ptr<dengine::GameObject> instance) const;
        double getDistanceTo(const dengine::vec3f& position) const;

        template <class T>
        std::shared_ptr<dengine::GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORM3DCOMPONENT_H
