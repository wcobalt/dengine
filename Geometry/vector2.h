//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_VECTOR2_H
#define DENGINE_VECTOR2_H

#include "vector3.h"

namespace dengine::geometry {
    template<class T>
    class vector2 : public vector3<T> {
    public:
        vector2();
        vector2(vector2<T>& vec);
        vector2(T x, T y);

        vector2<T>& operator=(vector2<T> b);
        vector2<T> operator+=(vector2<T> b);
        vector2<T> operator+(vector2<T> b);
        vector2<T> operator-=(vector2<T> b);
        vector2<T> operator-(vector2<T> b);
    };
}

#endif //DENGINE_VECTOR2_H
