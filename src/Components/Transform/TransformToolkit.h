//
// Created by wcobalt on 11/21/19.
//

#ifndef DENGINE_TRANSFORMTOOLKIT_H
#define DENGINE_TRANSFORMTOOLKIT_H

#include "../Toolkit.h"
#include "../../Math/Geometry.h"

namespace dengine {
    class TransformComponent;
    class GameObject;
    class Space;
}

namespace dengine {
    class TransformToolkit : public Toolkit {
    private:
        TransformComponent& transformComponent;
    public:
        explicit TransformToolkit(TransformComponent& transformComponent);

        double getDistanceTo(const GameObject& gameObject) const;

        double getDistanceTo(const TransformComponent& transform) const;

        double getDistanceTo(const vec3f& position) const;

        GameObject& getNearestInstance() const;

        GameObject& getNearestInstanceInSpace(Space& space) const;

        const vec3f & getParentPosition() const;

        //filters factories
    };
}

#endif //DENGINE_TRANSFORMTOOLKIT_H
