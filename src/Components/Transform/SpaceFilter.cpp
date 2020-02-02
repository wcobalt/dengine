//
// Created by wcobalt on 2/2/20.
//

#include "SpaceFilter.h"
#include "../../ComponentsManager.h"
#include "TransformComponent.h"
#include "../../GameObject.h"

using namespace dengine;

SpaceFilter::SpaceFilter(const Space &space) : space(space) {}

void SpaceFilter::init(CustomFilter::action_type action, std::unique_ptr<TraversalMethod> traversalMethod) {
    setAction(std::move(action));
    setTraversalMethod(std::move(traversalMethod));
    setSelection([this](const GameObject& gameObject) -> bool {
        return gameObject.getComponentsManager().getTransformComponent().getSpaces().isIn(this->space);
    });
}

const Space &SpaceFilter::getSpace() const {
    return space;
}
