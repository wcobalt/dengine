//
// Created by wcobalt on 11/18/19.
//

#include <queue>
#include <functional>
#include "Filter.h"
#include "../Dengine.h"
#include "../ScenesManager.h"
#include "../Scene.h"
#include "../GameObject.h"

using namespace dengine;

Filter::Filter(std::function<void(std::shared_ptr<GameObject>)> filterAction,
               std::function<bool(std::shared_ptr<GameObject>)> filterSelection, bool alwaysReturn)
               : filterSelection(filterSelection) {
    filterAction = [&filterAction, &alwaysReturn](std::shared_ptr<GameObject> gameObject) {
        filterAction(gameObject);

        return alwaysReturn;
    };
}

Filter::Filter(std::function<bool(std::shared_ptr<GameObject>)> filterAction,
               std::function<bool(std::shared_ptr<GameObject>)> filterSelection) : filterAction(filterAction),
                                                                                    filterSelection(filterSelection) {}

void Filter::run() const {
    runBfs();
}

void Filter::run(std::shared_ptr<GameObject> gameObject) const {
    runBfs(gameObject);
}

void Filter::runBfs() const {
    runBfs(false);
}

void Filter::runBfs(bool isReverse) const {
    std::shared_ptr<GameObject> root = getRoot();

    runBfs(root, isReverse);
}

void Filter::runBfs(std::shared_ptr<GameObject> gameObject) const {
    runBfs(gameObject, false);
}

void Filter::runBfs(std::shared_ptr<GameObject> gameObject, bool isReverse) const {
    std::queue<std::shared_ptr<GameObject>> queue;
    std::vector<std::shared_ptr<GameObject>> forHandle;

    queue.push(gameObject);

    while (!queue.empty()) {
        std::shared_ptr<GameObject> current = queue.front();

        if (isReverse)
            forHandle.emplace_back(current);
        else if (filterSelection(current))
            if (filterAction(current)) break;

        queue.pop();

        std::for_each(current->begin(), current->end(), [&queue](std::shared_ptr<GameObject> child) {
            queue.push(child);
        });
    }

    if (isReverse) {
        size_t size = forHandle.size();

        for (size_t i = size; i > 0; i--) {
            if (filterSelection(forHandle[i]))
                if (filterAction(forHandle[i])) break;
        }
    }
}

void Filter::runDfs() const {
    runDfs(getRoot());
}

void Filter::runDfs(std::shared_ptr<GameObject> gameObject) const {
    dfs(gameObject);
}

std::shared_ptr<GameObject> Filter::getRoot() const {
    return Dengine::get()->getScenesManager()->getCurrentScene()->getRoot();
}

bool Filter::dfs(std::shared_ptr<GameObject> gameObject) const {
    std::for_each(gameObject->begin(), gameObject->end(), [this](std::shared_ptr<GameObject> child) {
        if (filterSelection(child)) {
            if (filterAction(child)) return true;
        }

        if (dfs(child)) return true;
    });

    return false;
}
