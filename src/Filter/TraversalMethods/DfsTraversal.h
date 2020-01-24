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

        void dfs(GameObject &gameObject);
    public:
        explicit DfsTraversal(const Filter &filter);

        DfsTraversal(const Filter &filter, bool afterChildren);

        void run(GameObject &gameObject) override;
    };
}

#endif //DENGINE_DFSTRAVERSAL_H
