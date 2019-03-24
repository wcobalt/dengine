//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_VECTOR3F_H
#define DENGINE_VECTOR3F_H

namespace dengine::geometry {
    class vector3f {
    public:
        float x, y, z;

        vector3f();
        vector3f(vector3f& vec);
        vector3f(float x, float y, float z);

        float getModule();
        void normalize();
        vector3f getNormalizedVector();

        vector3f& operator=(vector3f b);
        vector3f operator+(vector3f b);
        vector3f operator-(vector3f b);
        vector3f operator-();
    };
}

#endif //DENGINE_VECTOR3F_H
