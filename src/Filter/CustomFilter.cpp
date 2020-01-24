//
// Created by wcobalt on 11/18/19.
//

#include "CustomFilter.h"
#include "../Dengine.h"
#include "TraversalMethod.h"

using namespace dengine;

//@fixme i don't know how to pass functions properly
CustomFilter::CustomFilter(action_type action, selection_type selection,
                           TraversalMethod &traversalMethod)
                           : traversalMethod(traversalMethod), action(action), selection(selection) {}

void CustomFilter::run() {
    run(Dengine::get().getScenesManager().getCurrentScene().getRoot());
}

void CustomFilter::run(GameObject &gameObject) {
    traversalMethod.run(*this, gameObject);
}

bool CustomFilter::check(const GameObject &gameObject) const {
    return selection(gameObject);
}

void CustomFilter::execute(GameObject &gameObject, TraversalMethod &traversalMethod) const {
    action(gameObject, traversalMethod);
}