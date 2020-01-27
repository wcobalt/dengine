#include "TransformComponent.h"
#include "../../Exceptions/ComponentException.h"
#include "../../Exceptions/LayerException.h"

using namespace dengine;

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject) : TransformComponent(gameObject, {}) {}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f &position)
    : TransformComponent(gameObject, position, {}, {1, 1, 1}) {}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject, float x, float y, float z)
    : TransformComponent(gameObject, {x, y, z}) {}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f &position,
                                       const Quaternion<float> &rotation, const vec3f &scale)
                                       : Component(gameObject), position(position), rotation(rotation), scale(scale) {}


void TransformComponent::setActive(bool isActive) {
    this->mIsActive = isActive;
}