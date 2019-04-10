//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_DENGINEACCESSOR_H
#define DENGINE_DENGINEACCESSOR_H

#include "Dengine.h"

namespace dengine {
    class DengineAccessor : public DObject {
        friend class Scene;
        friend class GameObject;
        friend class Dengine;
        friend class ScenesManager;
    private:
        DengineAccessor();
        DengineAccessor* operator=(DengineAccessor accessor);
    };
}

#endif //DENGINE_DENGINEACCESSOR_H
