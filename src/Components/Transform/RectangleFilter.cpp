//
// Created by wcobalt on 2/1/20.
//

#include "RectangleFilter.h"
#include "TransformComponent.h"
#include "../../ComponentsManager.h"
#include "../../GameObject.h"

using namespace dengine;

void RectangleFilter::init(float x1, float y1, float x2, float y2, CustomFilter::action_type action,
                           std::unique_ptr<TraversalMethod> traversalMethod) {
    init({x1, y1}, {x2, y2}, std::move(action), std::move(traversalMethod));
}

void RectangleFilter::init(vec2f point1, vec2f point2, CustomFilter::action_type action,
                           std::unique_ptr<TraversalMethod> traversalMethod) {
    init({point1, TransformComponent::MAX_DISTANCE}, {point2, TransformComponent::MAX_DISTANCE},
         std::move(action), std::move(traversalMethod));
}

void RectangleFilter::init(float x1, float y1, float z1, float x2, float y2, float z2, CustomFilter::action_type action,
                           std::unique_ptr<TraversalMethod> traversalMethod) {
    init({x1, y1, z1}, {x2, y2, z2}, std::move(action), std::move(traversalMethod));
}

void RectangleFilter::init(vec3f point1, vec3f point2, CustomFilter::action_type action,
                           std::unique_ptr<TraversalMethod> traversalMethod) {
    from = std::move(point1);
    to = std::move(point2);

    setAction(std::move(action));
    setTraversalMethod(std::move(traversalMethod));
    setSelection([this](const GameObject& gameObject) -> bool {
        vec3f pos = gameObject.getComponentsManager().getTransformComponent().getPosition();

        return (pos.x <= this->to.x && pos.x >= this->from.x &&
                pos.y <= this->to.y && pos.y >= this->from.y &&
                pos.z <= this->to.z && pos.z >= this->from.z);
    });
}

const vec3f &RectangleFilter::getFromPoint() const {
    return from;
}

const vec3f &RectangleFilter::getToPoint() const {
    return to;
}
