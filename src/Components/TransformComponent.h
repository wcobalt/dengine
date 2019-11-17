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
#include "../Math/vectors.h"

namespace dengine {
    class TransformComponent : public virtual BaseComponent {
    private:
        vec3f position;
        vec3f rotation;
        vec3f scale;
    public:
        TransformComponent();

        TransformComponent(const vec3f& position);

        TransformComponent(float x, float y, float z);

        TransformComponent(const vec3f& position, const vec3f& rotation,
                             const vec3f& scale);

        void setPosition(float x, float y, float z);

        void setPosition(const vec3f& vec);

        void setRotation(float x, float y, float z);

        void setRotation(const vec3f& vec);

        void setScale(float x, float y, float z);

        void setScale(const vec3f& vec);

        vec3f getPosition() const;

        vec3f getRotation() const;

        vec3f getScale() const;

        //@todo should they be here??? And what's about calculation distnace to transformcomponent rather than gameobject?
        double getDistanceTo(std::shared_ptr<GameObject> instance) const;

        double getDistanceTo(const vec3f& position) const;

        template <class T>
        std::shared_ptr<GameObject> getNearestInstance() const;
    };
}

#endif //DENGINE_TRANSFORM3DCOMPONENT_H
