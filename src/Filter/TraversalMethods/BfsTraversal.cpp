//
// Created by wcobalt on 1/23/20.
//
#include "BfsTraversal.h"
#include <queue>
#include "../Filter.h"
#include "../../GameObject.h"

using namespace dengine;

BfsTraversal::BfsTraversal(const Filter &filter) : BaseTraversal(filter) {}

void BfsTraversal::run(GameObject &gameObject) {
    mIsStopped = false;

    std::queue<GameObject*> queue;

    queue.emplace(&gameObject);

    while (!queue.empty()) {
        GameObject* go = queue.front();

        if (filter.check(*go))
            filter.execute(*go, *this);

        if (mIsStopped) break;

        queue.pop();

        for (GameObject* child : *go) {
            queue.push(child);
        }
    }
}
