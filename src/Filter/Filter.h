//
// Created by wcobalt on 11/18/19.
//
#include <memory>
#include <functional>

#ifndef DENGINE_FILTER_H
#define DENGINE_FILTER_H

namespace dengine {
    class GameObject;
}

namespace dengine {
    class Filter {
    private:
        std::function<void(std::shared_ptr<GameObject>)> filterAction;
        std::function<bool(std::shared_ptr<GameObject>)> filterSelection;

        std::shared_ptr<GameObject> getRoot() const;
    public:
        Filter(std::function<void(std::shared_ptr<GameObject>)> filterAction,
               std::function<bool(std::shared_ptr<GameObject>)> filterSelection);

        void run() const;

        void run(std::shared_ptr<GameObject> gameObject) const;

        void runBfs() const;

        void runBfs(bool isReverse) const;

        void runBfs(std::shared_ptr<GameObject> gameObject) const;

        void runBfs(std::shared_ptr<GameObject> gameObject, bool isReverse) const;

        void runDfs() const;

        void runDfs(std::shared_ptr<GameObject> gameObject) const;
    };
}

#endif //DENGINE_FILTER_H
