//
// Created by wcobalt on 11/21/19.
//

#ifndef DENGINE_TRANSFORMTOOLKIT_H
#define DENGINE_TRANSFORMTOOLKIT_H

#include "../Toolkit.h"
#include "../../Math/vectors.h"
#include "../../Filter/CustomFilter.h"
#include "DistanceFilter.h"

namespace dengine {
    class TransformComponent;
    class GameObject;
    class Space;
}

namespace dengine {
    class TransformToolkit : public Toolkit {
    private:
        TransformComponent& transformComponent;

        DistanceFilter filterByDistance(float distance, DistanceFilter::Distance type, CustomFilter::action_type action) const;
    public:
        explicit TransformToolkit(TransformComponent& transformComponent);

        float getDistanceTo(const GameObject& gameObject) const;

        float getDistanceTo(const TransformComponent& transform) const;

        float getDistanceTo(const vec3f& position) const;

        GameObject * getNearestInstance() const;

        GameObject * getNearestInstanceInSpace(Space& space) const;

        const vec3f & getParentPosition() const;

        DistanceFilter filterByMaximalDistance(float maximalDistance, CustomFilter::action_type filterAction) const;

        DistanceFilter filterByMinimalDistance(float minimalDistance, CustomFilter::action_type filterAction) const;
    };
}

#endif //DENGINE_TRANSFORMTOOLKIT_H
