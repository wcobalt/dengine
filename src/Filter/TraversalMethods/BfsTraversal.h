//
// Created by wcobalt on 1/23/20.
//

#ifndef DENGINE_BFSTRAVERSAL_H
#define DENGINE_BFSTRAVERSAL_H

#include "../TraversalMethods/BaseTraversal.h"

namespace dengine {
    class GameObject;
}

namespace dengine {
    class BfsTraversal : public BaseTraversal {
    public:
        void run(Filter &filter, GameObject &gameObject) override;
    };
}

#endif //DENGINE_BFSTRAVERSAL_H
