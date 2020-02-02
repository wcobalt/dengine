#include "TransformComponent.h"
#include "TransformToolkit.h"
#include "../../GameObject.h"
#include "../../ComponentsManager.h"
#include "../../Space.h"

using namespace dengine;

TransformComponent::TransformComponent(GameObject &gameObject) : TransformComponent(gameObject, {}) {}

TransformComponent::TransformComponent(GameObject &gameObject, const vec3f &position)
    : TransformComponent(gameObject, position, {}, {1, 1, 1}) {}

TransformComponent::TransformComponent(GameObject &gameObject, float x, float y, float z)
    : TransformComponent(gameObject, {x, y, z}) {}

TransformComponent::TransformComponent(GameObject &gameObject, const vec3f &position,
                                       const Quat &rotation, const vec3f &scale)
                                       : Component(gameObject), position(position),
                                         rotation(rotation), scale(scale),
                                         mIsActive(true), spacesContainer(std::make_unique<SpacesContainer>()),
                                         transformToolkit(std::make_unique<TransformToolkit>(*this)) {}

void TransformComponent::setActive(bool isActive) {
    this->mIsActive = isActive;
}

void TransformComponent::setPosition(const vec3f &position) {
    this->position = position;
}

void TransformComponent::setPosition(float x, float y, float z) {
    setPosition({x, y, z});
}

void TransformComponent::changePositionFor(const vec3f &delta) {
    position += delta;
}

void TransformComponent::changePositionFor(float x, float y, float z) {
    changePositionFor({x, y, z});
}

void TransformComponent::moveTo(const vec3f &position) {
    moveFor(position - this->position);
}

void TransformComponent::moveTo(float x, float y, float z) {
    moveTo({x, y, z});
}

void TransformComponent::moveFor(const vec3f &delta) {
    changePositionFor(delta);

    for (GameObject* child : gameObject) {
        child->getComponentsManager().getTransformComponent().moveFor(delta);
    }
}

void TransformComponent::moveFor(float x, float y, float z) {
    moveTo({x, y, z});
}

void TransformComponent::setRelativePosition(const vec3f &position) {
    this->position = transformToolkit->getParentPosition() + position;
}

void TransformComponent::setRelativePosition(float x, float y, float z) {
    setRelativePosition({x, y, z});
}

void TransformComponent::moveToRelative(const vec3f &position) {
    moveTo(transformToolkit->getParentPosition() + position);
}

void TransformComponent::moveToRelative(float x, float y, float z) {
    moveToRelative({x, y, z});
}

vec3f TransformComponent::getRelativePosition() const {
    vec3f parentPosition = transformToolkit->getParentPosition();

    //maybe it can be returned by const&???
    return parentPosition - position;
}

const vec3f & TransformComponent::getPosition() const {
    return position;
}

void TransformComponent::setRotation(const Quat &rotation) {
    this->rotation = rotation;
}

void TransformComponent::setScale(const vec3f &scale) {
    this->scale = scale;
}

void TransformComponent::setScale(float x, float y, float z) {
    this->scale = {x, y, z};
}

const Quat & TransformComponent::getRotation() const {
    return rotation;
}

const vec3f & TransformComponent::getScale() const {
    return scale;
}

//right hand coordinate system
//im totally not sure whether it's right or not
vec3f TransformComponent::up() const {
    return rotation * vec3f(0, 1, 0);
}

vec3f TransformComponent::front() const {
    return rotation * vec3f(0, 0, 1);
}

vec3f TransformComponent::left() const {
    return rotation * vec3f(1, 0, 0);
}

void TransformComponent::onAdditionToSpace(Space &space) {
    spacesContainer->addSpace(space);
}

void TransformComponent::onRemovalFromSpace(Space &space) {
    spacesContainer->removeSpace(space);
}

TransformComponent::SpacesContainer::Spaces TransformComponent::getSpaces() const {
    return spacesContainer->buildSpaces();
}

TransformToolkit & TransformComponent::getTransformToolkit() const {
    return *transformToolkit;
}

bool TransformComponent::isActive() const {
    return mIsActive;
}

std::unique_ptr<Component> TransformComponent::clone(GameObject &gameObject) const {
    std::unique_ptr<TransformComponent> clone = std::make_unique<TransformComponent>(gameObject);

    copyTo(*clone);

    return clone;
}

void TransformComponent::copy(const TransformComponent &from, TransformComponent &to, bool copyAll) {
    from.copyTo(to, copyAll);
}

void TransformComponent::copy(const GameObject &from, GameObject &to, bool copyAll) {
    from.getComponentsManager().getTransformComponent().copyTo(to, copyAll);
}

void TransformComponent::copyTo(TransformComponent &transform, bool copyAll) const {
    transform.position = position;
    transform.rotation = rotation;
    transform.scale = scale;

    if (copyAll) {
        transform.mIsActive = mIsActive;
        transform.spacesContainer = std::make_unique<SpacesContainer>(*spacesContainer);
    }
}

void TransformComponent::copyTo(GameObject &gameObject, bool copyAll) const {
    copyTo(gameObject.getComponentsManager().getTransformComponent(), copyAll);
}

//it's supposed that space wasn't added already (check is performed in SpacesManager)
void TransformComponent::SpacesContainer::addSpace(Space &space) {
    spaces.insert(&space);
}

//it's supposed that space was added already (check is performed in SpacesManager)
void TransformComponent::SpacesContainer::removeSpace(Space &space) {
    spaces.erase(&space);
}

TransformComponent::SpacesContainer::Spaces TransformComponent::SpacesContainer::buildSpaces() const {
    return Spaces{spaces};
}

TransformComponent::SpacesContainer::Spaces::Spaces(TransformComponent::SpacesContainer::Spaces::spaces_type &spaces) :
    spaces(spaces) {}

TransformComponent::SpacesContainer::Spaces::iterator TransformComponent::SpacesContainer::Spaces::begin() {
    return spaces.begin();
}

TransformComponent::SpacesContainer::Spaces::iterator TransformComponent::SpacesContainer::Spaces::end() {
    return spaces.end();
}

TransformComponent::SpacesContainer::Spaces::const_iterator TransformComponent::SpacesContainer::Spaces::begin() const {
    return spaces.begin();
}

TransformComponent::SpacesContainer::Spaces::const_iterator TransformComponent::SpacesContainer::Spaces::end() const {
    return spaces.end();
}

TransformComponent::SpacesContainer::Spaces::const_iterator
TransformComponent::SpacesContainer::Spaces::cbegin() const {
    return spaces.cbegin();
}

TransformComponent::SpacesContainer::Spaces::const_iterator TransformComponent::SpacesContainer::Spaces::cend() const {
    return spaces.cend();
}

bool TransformComponent::SpacesContainer::Spaces::isIn(const Space &space) const {
    for (auto currentSpace : *this) {
        if (*currentSpace == space) return true;
    }

    return false;
}
