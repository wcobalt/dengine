//
// Created by wcobalt on 11/18/19.
//
#include <memory>
#include <functional>

#ifndef DENGINE_FILTER_H
#define DENGINE_FILTER_H

namespace dengine {
    class GameObject;
    class TraversalMethod;
}

namespace dengine {
    class Filter {
    public:
        virtual void run() = 0;

        virtual void run(GameObject &gameObject) = 0;

        virtual bool check(const GameObject& gameObject) const = 0;

        virtual void execute(GameObject &gameObject, TraversalMethod &traversalMethod) = 0;

        virtual void setTraversalMethod(std::unique_ptr<TraversalMethod> traversalMethod) = 0;

        virtual TraversalMethod & getTraversalMethod() const = 0;
    };
}

#endif //DENGINE_FILTER_H
