//
// Created by wcobalt on 3/26/19.
//

#ifndef DENGINE_DIMENSION3_H
#define DENGINE_DIMENSION3_H

#include "vector3.h"

namespace dengine::geometry {
    template<class T>
    class dimension3 {
    public:
        T width, height, depth;

        dimension3();
        dimension3(vector3<T> vec);
        dimension3(const dimension3<T> &dimension);
        dimension3(T width, T height, T depth);
    };
}

#endif //DENGINE_DIMENSION3_H
