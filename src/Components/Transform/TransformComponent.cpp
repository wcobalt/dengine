#include "TransformComponent.h"

using namespace dengine;

TransformComponent::TransformComponent(GameObject &gameObject) : TransformComponent(gameObject, {}) {}

TransformComponent::TransformComponent(GameObject &gameObject, const vec3f &position)
    : TransformComponent(gameObject, position, {}, {1, 1, 1}) {}

TransformComponent::TransformComponent(GameObject &gameObject, float x, float y, float z)
    : TransformComponent(gameObject, {x, y, z}) {}

TransformComponent::TransformComponent(GameObject &gameObject, const vec3f &position,
                                       const Quaternion<float> &rotation, const vec3f &scale)
                                       : Component(gameObject), position(position), rotation(rotation), scale(scale),
                                       mIsActive(true) {}


void TransformComponent::setActive(bool isActive) {
    this->mIsActive = isActive;
}