//
// Created by wcobalt on 3/26/19.
//

#ifndef DENGINE_DIMENSION2_H
#define DENGINE_DIMENSION2_H

#include "dimension3.h"
#include "vector2.h"

namespace dengine::geometry {
    template<class T>
    class dimension2 : public dimension3<T> {
    private:
        T depth;
    public:
        dimension2();
        dimension2(vector2<T> vec);
        dimension2(const dimension2<T> &dimension);
        dimension2(const dimension3<T> &dimension);
        dimension2(T width, T height);
    };
}

#endif //DENGINE_DIMENSION2_H
