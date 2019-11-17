//
// Created by wcobalt on 2/23/19.
//

#include <queue>
#include <vector>
#include <float.h>
#include <memory>

#include "TransformComponent.h"
#include "../Math/Geometry.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "../Dengine.h"
#include "../ScenesManager.h"

using namespace dengine;

using std::queue;
using std::vector;
using std::shared_ptr;

TransformComponent::TransformComponent() = default;

TransformComponent::TransformComponent(const vec3f& position):position(position) {}

TransformComponent::TransformComponent(float x, float y, float z):position(vec3f(x, y, z)) {}

TransformComponent::TransformComponent(const vec3f& position, const vec3f& rotation, const vec3f& scale):
    position(position),
    rotation(rotation),
    scale(scale) {}

void TransformComponent::setPosition(float x, float y, float z) {
    setPosition(vec3f(x, y, z));
}

void TransformComponent::setPosition(const vec3f& vec) {
    vec3f delta = vec - position;

    position = vec;

    vector<shared_ptr<GameObject>> children = getBoundInstance()->getChildren();

    for (shared_ptr<GameObject>& child : children) {
        shared_ptr<TransformComponent> transform = child->getComponent<TransformComponent>();

        transform->setPosition(transform->getPosition() + delta);
    }
}

void TransformComponent::setRotation(float x, float y, float z) {
    setRotation(vec3f(x, y, z));
}

void TransformComponent::setRotation(const vec3f& vec) {
    vec3f delta = vec - rotation;

    rotation = vec;

    vector<shared_ptr<GameObject>> children = getBoundInstance()->getChildren();

    for (shared_ptr<GameObject>& child : children) {
        shared_ptr<TransformComponent> transform = child->getComponent<TransformComponent>();

        transform->setRotation(transform->getRotation() + delta);
    }
}

void TransformComponent::setScale(float x, float y, float z) {
    setScale(vec3f(x, y, z));
}

void TransformComponent::setScale(const vec3f& vec) {
    vec3f delta = vec - scale;

    scale = vec;

    vector<shared_ptr<GameObject>> children = getBoundInstance()->getChildren();

    for (shared_ptr<GameObject>& child : children) {
        shared_ptr<TransformComponent> transform = child->getComponent<TransformComponent>();

        transform->setScale(transform->getScale() + delta);
    }
}

vec3f TransformComponent::getPosition() const {
    return position;
}

vec3f TransformComponent::getRotation() const {
    return rotation;
}

vec3f TransformComponent::getScale() const {
    return scale;
}

double TransformComponent::getDistanceTo(shared_ptr<GameObject> instance) const {
    return Geometry::getDistance(this->getPosition(),
            instance->getComponent<TransformComponent>()->getPosition());
}

double TransformComponent::getDistanceTo(const vec3f& position) const {
    return Geometry::getDistance(this->getPosition(), position);
}

template <class T>
shared_ptr<GameObject> TransformComponent::getNearestInstance() const {
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