//
// Created by wcobalt on 1/24/20.
//

#ifndef DENGINE_DFSTRAVERSAL_H
#define DENGINE_DFSTRAVERSAL_H

#include "BaseTraversal.h"

namespace dengine {
    class DfsTraversal : public BaseTraversal {
    private:
        bool afterChildren;

        void dfs(Filter &filter, GameObject &gameObject);
    public:
        DfsTraversal();

        explicit DfsTraversal(bool afterChildren);

        void run(Filter &filter, GameObject &gameObject) override;
    };
}

#endif //DENGINE_DFSTRAVERSAL_H
