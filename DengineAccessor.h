//
// Created by wcobalt on 4/6/19.
//

#ifndef DENGINE_DENGINEACCESSOR_H
#define DENGINE_DENGINEACCESSOR_H

namespace dengine {
    class Scene;
    class GameObject;
    class Dengine;
    class ScenesManager;
}

namespace dengine {
    class ScenesManager;

    class DengineAccessor {
        friend class Scene;
        friend class GameObject;
        friend class Dengine;
        friend class ScenesManager;
    private:
        DengineAccessor();
        DengineAccessor& operator=(const DengineAccessor& accessor);
    };
}

#endif //DENGINE_DENGINEACCESSOR_H
