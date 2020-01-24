//
// Created by wcobalt on 1/24/20.
//

#include "DfsTraversal.h"
#include "../../GameObject.h"
#include "../Filter.h"

using namespace dengine;

DfsTraversal::DfsTraversal(const Filter &filter) : BaseTraversal(filter), afterChildren(false) {}

DfsTraversal::DfsTraversal(const Filter &filter, bool afterChildren) : BaseTraversal(filter),
                                                                       afterChildren(afterChildren) {}

void DfsTraversal::run(GameObject &gameObject) {
    mIsStopped = false;

    dfs(gameObject);
}

void DfsTraversal::dfs(GameObject &gameObject) {
    if (!afterChildren) {
        filter.execute(gameObject, *this);

        if (mIsStopped) return; //stop initialization
    }

    for (GameObject* child : gameObject) {
        dfs(*child);

        if (mIsStopped) return; //stop propagation
    }

    if (afterChildren)
        filter.execute(gameObject, *this); //stop initialization
}
