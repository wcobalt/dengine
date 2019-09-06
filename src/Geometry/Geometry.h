//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_GEOMETRY_H
#define DENGINE_GEOMETRY_H

#include "vectors.h"

namespace dengine {
    class Geometry {
    public:
        static double getDistance(const vec3f& from, const vec3f& to);
    };
}

#endif //DENGINE_GEOMETRY_H
