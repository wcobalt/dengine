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
        std::function<bool(std::shared_ptr<GameObject>)> filterAction;
        std::function<bool(std::shared_ptr<GameObject>)> filterSelection;

        std::shared_ptr<GameObject> getRoot() const;

        bool dfs(std::shared_ptr<GameObject> gameObject) const;
    public:
        Filter(std::function<void(std::shared_ptr<GameObject>)> filterAction,
               std::function<bool(std::shared_ptr<GameObject>)> filterSelection, bool alwaysReturn);

        Filter(std::function<bool(std::shared_ptr<GameObject>)> filterAction,
               std::function<bool(std::shared_ptr<GameObject>)> filterSelection);

        virtual void run() const;

        virtual void run(std::shared_ptr<GameObject> gameObject) const;

        virtual void runBfs() const;

        virtual void runBfs(bool isReverse) const;

        virtual void runBfs(std::shared_ptr<GameObject> gameObject) const;

        virtual void runBfs(std::shared_ptr<GameObject> gameObject, bool isReverse) const;

        virtual void runDfs() const;

        virtual void runDfs(std::shared_ptr<GameObject> gameObject) const;
    };
}

#endif //DENGINE_FILTER_H
