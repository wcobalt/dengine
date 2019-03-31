//
// Created by wcobalt on 3/30/19.
//

#include "Transform2DComponent.h"

using namespace dengine::components;

Transform2DComponent::Transform2DComponent() = default;

Transform2DComponent::Transform2DComponent(vec2f position):Transform3DComponent(position) {}

Transform2DComponent::Transform2DComponent(float x, float y):Transform3DComponent(x, y, 0) {}

Transform2DComponent::Transform2DComponent(vec2f position, vec2f rotation, vec2f scale):
        Transform3DComponent(position, rotation, scale) {}

void Transform2DComponent::setPosition(float x, float y) {
    vec3f position = Transform3DComponent::getPosition();

    Transform3DComponent::setPosition(x, y, position.z);
}

void Transform2DComponent::setRotation(float x, float y) {
    vec3f rotation = Transform3DComponent::getRotation();

    Transform3DComponent::setRotation(x, y, rotation.z);
}

void Transform2DComponent::setScale(float x, float y) {
    vec3f scale = Transform3DComponent::getScale();

    Transform3DComponent::setScale(x, y, scale.z);
}

vec2f Transform2DComponent::getPosition() const {
    return vec2f(Transform3DComponent::getPosition());
}

vec2f Transform2DComponent::getRotation() const {
    return vec2f(Transform3DComponent::getRotation());
}

vec2f Transform2DComponent::getScale() const {
    return vec2f(Transform3DComponent::getScale());
}

double Transform2DComponent::getDistanceTo(vec2f position) const {
    return Transform3DComponent::getDistanceTo(position);
}