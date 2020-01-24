//
// Created by wcobalt on 1/23/20.
//

#ifndef DENGINE_BASETRAVERSAL_H
#define DENGINE_BASETRAVERSAL_H

#include "../TraversalMethod.h"

namespace dengine {
    class BaseTraversal : public TraversalMethod {
    protected:
        const Filter& filter;
        bool mIsStopped;
    public:
        explicit BaseTraversal(const Filter& filter);

        void stop() override;

        bool isStopped() const override;

        const Filter& getFilter() const {
            return filter;
        }
    };
}

#endif //DENGINE_BASETRAVERSAL_H
