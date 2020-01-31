//
// Created by wcobalt on 1/31/20.
//

#ifndef DENGINE_TOOLKIT_H
#define DENGINE_TOOLKIT_H

#include "../DObject.h"

namespace dengine {
    class Scene;
}

namespace dengine {
    class Toolkit : public DObject {
    public:
        virtual Scene& getCurrentScene() const;
    };
}

#endif //DENGINE_TOOLKIT_H
