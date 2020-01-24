//
// Created by wcobalt on 1/23/20.
//

#ifndef DENGINE_BASETRAVERSAL_H
#define DENGINE_BASETRAVERSAL_H

#include "../TraversalMethod.h"

namespace dengine {
    class BaseTraversal : public TraversalMethod {
    protected:
        bool mIsStopped;
    public:
        BaseTraversal();

        void setStopped(bool isStopped) override;

        bool isStopped() const override;
    };
}

#endif //DENGINE_BASETRAVERSAL_H
