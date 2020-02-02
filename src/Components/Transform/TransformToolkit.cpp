//
// Created by wcobalt on 11/21/19.
//

#include "TransformToolkit.h"
#include "TransformComponent.h"
#include "../../Math/Geometry.h"
#include "../../GameObject.h"
#include "../../ComponentsManager.h"
#include "../../Filter/CustomFilter.h"
#include "../../Filter/TraversalMethods/BfsTraversal.h"
#include "../../SpacesManager.h"
#include "../../Scene.h"
#include "../../Space.h"

using namespace dengine;

TransformToolkit::TransformToolkit(TransformComponent &transformComponent) : Toolkit(transformComponent),
                                                                             transformComponent(transformComponent) {}

float TransformToolkit::getDistanceTo(const GameObject &gameObject) const {
    return getDistanceTo(gameObject.getComponentsManager().getTransformComponent());
}

float TransformToolkit::getDistanceTo(const TransformComponent &transform) const {
    return getDistanceTo(transform.getPosition());
}

float TransformToolkit::getDistanceTo(const vec3f &position) const {
    return Geometry::getDistance(position, transformComponent.getPosition());
}

GameObject * TransformToolkit::getNearestInstance() const {
    float minimalDistance = TransformComponent::MAX_DISTANCE;
    GameObject* nearestInstance = nullptr;

    CustomFilter filter(
            [&minimalDistance, &nearestInstance, this](GameObject& gameObject, TraversalMethod& traversalMethod) {
                float distance = getDistanceTo(gameObject);

                if (distance < minimalDistance) {
                    nearestInstance = &gameObject;
                    minimalDistance = distance;
                }
            },
            [](const GameObject& gameObject) -> bool {
                return true;
            });

    filter.run();

    return nearestInstance;
}

GameObject * TransformToolkit::getNearestInstanceInSpace(Space &space) const {
    float minimalDistance = TransformComponent::MAX_DISTANCE;
    GameObject* nearestInstance = nullptr;

    for (auto go : space) {
        float distance = getDistanceTo(*go);

        if (distance < minimalDistance) {
            nearestInstance = go;
            minimalDistance = distance;
        }
    }

    return nearestInstance;
}

const vec3f & TransformToolkit::getParentPosition() const {
    return transformComponent.getGameObject().getParent().getComponentsManager().getTransformComponent().getPosition();
}

DistanceFilter
TransformToolkit::filterByMaximalDistance(float maximalDistance, CustomFilter::action_type filterAction) const {
    return filterByDistance(maximalDistance, DistanceFilter::Distance::MAXIMAL, std::move(filterAction));
}

DistanceFilter
TransformToolkit::filterByMinimalDistance(float minimalDistance, CustomFilter::action_type filterAction) const {
    return filterByDistance(minimalDistance, DistanceFilter::Distance::MINIMAL, std::move(filterAction));
}

DistanceFilter
TransformToolkit::filterByDistance(float distance, DistanceFilter::Distance type, CustomFilter::action_type action) const {
    DistanceFilter distanceFilter;

    distanceFilter.init(transformComponent.getPosition(), distance, type,
                        std::move(action));

    return distanceFilter;
}
