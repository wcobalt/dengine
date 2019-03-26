//
// Created by wcobalt on 2/23/19.
//

#include "Transform3DComponent.h"

using namespace dengine::components;

Transform3DComponent::Transform3DComponent() = default;

void Transform3DComponent::componentLoad() {

}

void Transform3DComponent::componentUnload() {

}

void Transform3DComponent::update() {

}

void Transform3DComponent::instanceCreated() {

}

void Transform3DComponent::instanceDestroyed() {

}

void Transform3DComponent::setPosition(float x, float y, float z) {
    position = vec3f(x, y, z);
}

void Transform3DComponent::setPosition(vec3f vec) {
    position = vec3f(vec);
}

void Transform3DComponent::setRotation(float x, float y, float z) {
    rotation = vec3f(x, y, z);
}

void Transform3DComponent::setRotation(vec3f vec) {
    rotation = vec3f(vec);
}

void Transform3DComponent::setScale(float x, float y, float z) {
    scale = vec3f(x, y, z);
}

void Transform3DComponent::setScale(vec3f vec) {
    scale = vec3f(vec);
}

vec3f Transform3DComponent::getPosition() {
    return position;
}

vec3f Transform3DComponent::getRotation() {
    return rotation;
}

vec3f Transform3DComponent::getScale() {
    return scale;
}