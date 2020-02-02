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
    public:
        using action_type = std::function<void(GameObject&, TraversalMethod&)>;
        using selection_type = std::function<bool(const GameObject&)>;
    private:
        std::unique_ptr<TraversalMethod> traversalMethod;

        action_type action;
        selection_type selection;
    public:
        CustomFilter() = default;

        CustomFilter(action_type action, selection_type selection,
                     std::unique_ptr<TraversalMethod> traversalMethod = std::make_unique<TraversalMethod>());

        void run() override;

        void run(GameObject &gameObject) override;

        bool check(const GameObject &gameObject) const override;

        void execute(GameObject &gameObject, TraversalMethod &traversalMethod) override;

        void setAction(action_type action);

        void setSelection(selection_type selection);

        TraversalMethod & getTraversalMethod() const override {
            return *traversalMethod;
        }

        void setTraversalMethod(std::unique_ptr<TraversalMethod> traversalMethod) override;
    };
}

#endif //DENGINE_CUSTOMFILTER_H
