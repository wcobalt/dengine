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

using namespace dengine;

TransformToolkit::TransformToolkit(TransformComponent &transformComponent) : Toolkit(transformComponent),
                                                                             transformComponent(transformComponent) {}

double TransformToolkit::getDistanceTo(const GameObject &gameObject) const {
    return getDistanceTo(gameObject.getComponentsManager().getTransformComponent());
}

double TransformToolkit::getDistanceTo(const TransformComponent &transform) const {
    return getDistanceTo(transform.getPosition());
}

double TransformToolkit::getDistanceTo(const vec3f &position) const {
    return Geometry::getDistance(position, transformComponent.getPosition());
}

GameObject &TransformToolkit::getNearestInstance() const {
    return getNearestInstanceInSpace(getCurrentScene().getSpace(Scene::StandardSpace::GLOBAL));

    double minimalDistance = 10e9;
    GameObject* nearestInstance = nullptr;

    BfsTraversal bfsTraversal;

    CustomFilter filter(
           [&minimalDistance, &nearestInstance, this](GameObject& gameObject, TraversalMethod& traversalMethod) {
                    double distance = getDistanceTo(gameObject);

                    if (distance < minimalDistance) {
                        nearestInstance = &gameObject;
                        minimalDistance = distance;
                    }
                 },
                 [](const GameObject& gameObject) -> bool {
                     return true;
                 },
                 bfsTraversal);

    filter.run();

    return nearestInstance != nullptr ? *nearestInstance : transformComponent.getGameObject();
}

GameObject &TransformToolkit::getNearestInstanceInSpace(Space &space) const {
    //trough TransformComponent's filters
    return <#initializer#>;
}

const vec3f & TransformToolkit::getParentPosition() const {
    return transformComponent.getGameObject().getParent().getComponentsManager().getTransformComponent().getPosition();
}
