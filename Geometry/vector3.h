//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_VECTOR3_H
#define DENGINE_VECTOR3_H

namespace dengine::geometry {
    template<typename T>
    class vector3 {
    public:
        T x, y, z;

        vector3();
        vector3(vector3& vec);
        vector3(T x, T y, T z);

        T getModule();
        void normalize();
        vector3 getNormalizedVector();

        vector3& operator=(vector3 b);
        vector3 operator+=(vector3 b);
        vector3 operator+(vector3 b);
        vector3 operator-=(vector3 b);
        vector3 operator-(vector3 b);
        vector3 operator-();
    };
}

#endif //DENGINE_VECTOR3_H
