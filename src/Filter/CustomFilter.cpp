//
// Created by wcobalt on 11/18/19.
//

#include "CustomFilter.h"
#include "../Dengine.h"
#include "TraversalMethod.h"
#include "../ScenesManager.h"
#include "../Scene.h"

using namespace dengine;

CustomFilter::CustomFilter(action_type action, selection_type selection,
                           std::unique_ptr<TraversalMethod> traversalMethod)
                           : traversalMethod(std::move(traversalMethod)),
                           action(std::move(action)), selection(std::move(selection)) {}

void CustomFilter::run() {
    run(Dengine::get().getScenesManager().getCurrentScene().getRoot());
}

void CustomFilter::run(GameObject &gameObject) {
    traversalMethod->run(*this, gameObject);
}

bool CustomFilter::check(const GameObject &gameObject) const {
    return selection(gameObject);
}

void CustomFilter::execute(GameObject &gameObject, TraversalMethod &traversalMethod) {
    action(gameObject, traversalMethod);
}

void CustomFilter::setTraversalMethod(std::unique_ptr<TraversalMethod> traversalMethod) {
    this->traversalMethod = std::move(traversalMethod);
}

void CustomFilter::setAction(CustomFilter::action_type action) {
    this->action = std::move(action);
}

void CustomFilter::setSelection(CustomFilter::selection_type selection) {
    this->selection = std::move(selection);
}