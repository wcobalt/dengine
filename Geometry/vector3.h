//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_VECTOR3_H
#define DENGINE_VECTOR3_H

#include "../DObject.h"

namespace dengine::geometry {
    template<typename T>
    class vector3 : public DObject {
    public:
        T x, y, z;

        vector3();
        vector3(const vector3<T>& vec);
        vector3(T x, T y, T z);

        T getModule() const;
        void normalize();
        vector3<T> getNormalizedVector() const;

        vector3<T>& operator=(const vector3<T>& b);
        vector3<T> operator+=(vector3<T> b);
        vector3<T> operator+(vector3<T> b);
        vector3<T> operator-=(vector3<T> b);
        vector3<T> operator-(vector3<T> b);
        vector3<T> operator-();
    };
}

#endif //DENGINE_VECTOR3_H
