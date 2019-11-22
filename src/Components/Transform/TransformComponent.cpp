#include "TransformComponent.h"
#include "../../Exceptions/ComponentException.h"
#include "../../Exceptions/LayerException.h"
#include "../../Layer.h"

using namespace dengine;

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject) : TransformComponent(gameObject, {}) {}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f &position)
    : TransformComponent(gameObject, position, {}, {1, 1, 1}) {}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject, float x, float y, float z)
    : TransformComponent(gameObject, {x, y, z}) {}

TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject, const vec3f &position,
                                       const Quaternion<float> &rotation, const vec3f &scale)
                                       : Component(gameObject), position(position), rotation(rotation), scale(scale) {}

void TransformComponent::addToLayer(std::shared_ptr<Layer> layer) {
    auto it = findLayer(layer);

    if (it == layers.end()) {
        layers.insert(std::make_pair(layer, true));
    } else
        throw LayerException("The game object is on the layer " + layer->getName() + " already:");
}

bool TransformComponent::isOnLayer(std::shared_ptr<Layer> layer) const {
    return findLayer(layer) != layers.end();
}

void TransformComponent::setTagName(const std::string &tagName) {
    this->tagName = tagName;
}

void TransformComponent::setActive(bool isActive) {
    this->mIsActive = isActive;
}

TransformComponent::const_layers_iterator TransformComponent::findLayer(std::shared_ptr<Layer> layer) const {
    for (auto it = layers.begin(); it != layers.end(); it++)
        if (*it->first == *layer) return it;

    return layers.end();
}
