//
// Created by wcobalt on 2/1/20.
//

#include "DistanceFilter.h"
#include "../../Math/Geometry.h"
#include "TransformComponent.h"
#include "../../GameObject.h"
#include "../../ComponentsManager.h"
#include "TransformToolkit.h"

using namespace dengine;

float DistanceFilter::getMinimalDistance() const {
    return minimalDistance;
}

float DistanceFilter::getMaximalDistance() const {
    return maximalDistance;
}

const vec3f &DistanceFilter::getOrigin() const {
    return origin;
}

void
DistanceFilter::init(vec3f origin, float distance, Distance type, action_type action,
                     std::unique_ptr<TraversalMethod> traversalMethod) {
    float minDistance, maxDistance;

    switch (type) {
        case Distance::MINIMAL:
            minDistance = distance;
            maxDistance = TransformComponent::MAX_DISTANCE;

            break;

        case Distance::MAXIMAL:
            minDistance = 0;
            maxDistance = distance;

            break;
    }

    init(std::move(origin), minDistance, maxDistance, std::move(action), std::move(traversalMethod));
}

void DistanceFilter::init(vec3f origin, float minimalDistance, float maximalDistance, CustomFilter::action_type action,
                          std::unique_ptr<TraversalMethod> traversalMethod) {
    this->origin = std::move(origin);
    this->minimalDistance = minimalDistance;
    this->maximalDistance = maximalDistance;

    setSelection([this](const GameObject& gameObject) -> bool {
        vec3f position = gameObject.getComponentsManager().getTransformComponent().getPosition();
        float distance = Geometry::getDistance(this->origin, position);

        return (distance <= this->maximalDistance && distance >= this->minimalDistance);
    });

    setAction(std::move(action));
    setTraversalMethod(std::move(traversalMethod));
}
