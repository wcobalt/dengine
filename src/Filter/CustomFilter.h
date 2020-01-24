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

        TraversalMethod& traversalMethod;

        action_type action;
        selection_type selection;
    public:
        CustomFilter(action_type action, selection_type selection,
                     TraversalMethod &traversalMethod);

        void run() override;

        void run(GameObject &gameObject) override;

        bool check(const GameObject &gameObject) const override;

        void execute(GameObject &gameObject, TraversalMethod &traversalMethod) const override;

        const TraversalMethod &getTraversalMethod() const override {
            return traversalMethod;
        }
    };
}

#endif //DENGINE_CUSTOMFILTER_H
