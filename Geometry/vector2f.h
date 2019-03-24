//
// Created by wcobalt on 3/23/19.
//

#ifndef DENGINE_VECTOR2F_H
#define DENGINE_VECTOR2F_H

#include "vector3f.h"

namespace dengine::geometry {
    class vector2f : public vector3f {
    public:
        vector2f();
        vector2f(vector2f& vec);
        vector2f(float x, float y);

        vector2f getNormalizedVector();

        vector2f& operator=(vector2f b);
        vector2f operator+(vector2f b);
        vector2f operator-(vector2f b);
        vector2f operator-();
    };
}

#endif //DENGINE_VECTOR2F_H
