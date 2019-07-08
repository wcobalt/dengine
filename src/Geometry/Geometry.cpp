//
// Created by wcobalt on 3/30/19.
//

#include <cmath>

#include "Geometry.h"

using namespace dengine::geometry;

double Geometry::getDistance(const vec3f& from, const vec3f& to) {
    return sqrt(pow(from.x - to.x, 2.0) + pow(from.y - to.y, 2.0) + pow(from.z - to.z, 2.0));
}