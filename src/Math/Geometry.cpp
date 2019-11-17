//
// Created by wcobalt on 3/30/19.
//

#include <cmath>

#include "Geometry.h"
#include "vectors.h"
#include "Number.h"

using namespace dengine;

double Geometry::getDistance(const vec3f &from, const vec3f &to) {
    return (from - to).getModulo();
}

double Geometry::getDistance(const vec2f &from, const vec2f &to) {
    return (from - to).getModulo();
}

double Geometry::getAngle(const vec3f &a, const vec3f &b) {
    return calculateAngle(a, b);
}

double Geometry::getAngle(const vec2f &a, const vec2f &b) {
    return calculateAngle(a, b);
}

template<typename T>
double Geometry::calculateAngle(const T &a, const T &b) {
    double cosine = a.scalar(b) / (a.getModulo() * b.getModulo());

    return acos(std::min(std::max(cosine, -1.0), 1.0));
}


