//
// Created by wcobalt on 2/23/19.
//

#include <queue>
#include <vector>
#include <float.h>
#include <memory>

#include "Transform3DComponent.h"
#include "../Geometry/Geometry.h"
#include "../GameObject.h"
#include "../Scene.h"

using namespace dengine;
using namespace dengine::components;
using namespace dengine::geometry;

using std::queue;
using std::vector;
using std::shared_ptr;

Transform3DComponent::Transform3DComponent() = default;

Transform3DComponent::Transform3DComponent(vec3f position) {
    this->position = position;
}

Transform3DComponent::Transform3DComponent(float x, float y, float z) {
    this->position = vec3f(x, y, z);
}

Transform3DComponent::Transform3DComponent(vec3f position, vec3f rotation, vec3f scale) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

void Transform3DComponent::setPosition(float x, float y, float z) {
    setPosition(vec3f(x, y, z));
}

void Transform3DComponent::setPosition(vec3f vec) {
    vec3f delta = vec - position;

    position = vec3f(vec);

    vector<shared_ptr<GameObject>> children = getBoundInstance()->getChildren();

    for (shared_ptr<GameObject>& child : children) {
        shared_ptr<Transform3DComponent> transform = child->getComponent<Transform3DComponent>();

        vec3f childPosition = transform->getPosition();

        transform->setPosition(childPosition + delta);
    }
}

void Transform3DComponent::setRotation(float x, float y, float z) {
    setRotation(vec3f(x, y, z));
}

void Transform3DComponent::setRotation(vec3f vec) {
    vec3f delta = vec - rotation;

    rotation = vec3f(vec);

    vector<shared_ptr<GameObject>> children = getBoundInstance()->getChildren();

    for (shared_ptr<GameObject>& child : children) {
        shared_ptr<Transform3DComponent> transform = child->getComponent<Transform3DComponent>();

        vec3f childRotation = transform->getRotation();

        transform->setRotation(childRotation + delta);
    }
}

void Transform3DComponent::setScale(float x, float y, float z) {
    setScale(vec3f(x, y, z));
}

void Transform3DComponent::setScale(vec3f vec) {
    vec3f delta = vec - scale;

    scale = vec3f(vec);

    vector<shared_ptr<GameObject>> children = getBoundInstance()->getChildren();

    for (shared_ptr<GameObject>& child : children) {
        shared_ptr<Transform3DComponent> transform = child->getComponent<Transform3DComponent>();

        vec3f childScale = transform->getScale();

        transform->setRotation(childScale + delta);
    }
}

vec3f Transform3DComponent::getPosition() const {
    return position;
}

vec3f Transform3DComponent::getRotation() const {
    return rotation;
}

vec3f Transform3DComponent::getScale() const {
    return scale;
}

double Transform3DComponent::getDistanceTo(shared_ptr<GameObject> instance) const {
    return Geometry::getDistance(this->getPosition(),
            instance->getComponent<Transform3DComponent>()->getPosition());
}

double Transform3DComponent::getDistanceTo(vec3f position) const {
    return Geometry::getDistance(this->getPosition(), position);
}

template<class T>
shared_ptr<GameObject> Transform3DComponent::getNearestInstance() const {
    shared_ptr<Scene> currentScene = Dengine::get()->getScenesManager()->getCurrentScene();

    shared_ptr<GameObject> root = currentScene->getRoot();


    shared_ptr<GameObject> result;

    {
        double minDistance = DBL_MAX;

        queue<shared_ptr<GameObject>> q;

        q.push(root);

        while (!q.empty()) {
            shared_ptr<GameObject> currentInstance = q.front();

            q.pop();

            vector<shared_ptr<GameObject>> children = currentInstance->getChildren();

            for (const auto &instance : children)
                q.push(instance);

            if (currentInstance != root &&
                std::dynamic_pointer_cast<T>(currentInstance)) {

                double distance = getDistanceTo(currentInstance);

                if (distance < minDistance) {
                    minDistance = distance;

                    result = currentInstance;
                }
            }
        }
    }

    return result;
}