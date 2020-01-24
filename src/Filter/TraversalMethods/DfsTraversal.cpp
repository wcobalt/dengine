//
// Created by wcobalt on 1/24/20.
//

#include "DfsTraversal.h"
#include "../../GameObject.h"
#include "../Filter.h"

using namespace dengine;

DfsTraversal::DfsTraversal() : afterChildren(false) {}

DfsTraversal::DfsTraversal(bool afterChildren) : afterChildren(afterChildren) {}

void DfsTraversal::run(Filter &filter, GameObject &gameObject) {
    setStopped(false);

    dfs(filter, gameObject);
}

void DfsTraversal::dfs(Filter &filter, GameObject &gameObject) {
    if (!afterChildren) {
        filter.execute(gameObject, *this);

        if (isStopped()) return; //stop initialization
    }

    for (GameObject* child : gameObject) {
        dfs(filter, *child);

        if (isStopped()) return; //stop propagation
    }

    if (afterChildren)
        filter.execute(gameObject, *this); //stop initialization
}
