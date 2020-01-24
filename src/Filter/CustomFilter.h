//
// Created by wcobalt on 1/23/20.
//

#ifndef DENGINE_CUSTOMFILTER_H
#define DENGINE_CUSTOMFILTER_H

#include "Filter.h"

namespace dengine {
    class TraversalMethod;
}

namespace dengine {
    class CustomFilter : public Filter {
    private:
        using action_type = std::function<void(GameObject&, TraversalMethod&)>;
        using selection_type = std::function<bool(const GameObject&)>;

        const TraversalMethod& traversalMethod;

        action_type action;
        selection_type selection;
    public:
        explicit CustomFilter(action_type action, selection_type selection,
                              const TraversalMethod& traversalMethod);

        void run() const override;

        void run(GameObject &gameObject) const override;

        bool check(const GameObject &gameObject) const override;

        void execute(GameObject &gameObject, TraversalMethod &traversalMethod) const override;

        const TraversalMethod &getTraversalMethod() const override {
            return traversalMethod;
        }
    };
}

#endif //DENGINE_CUSTOMFILTER_H
