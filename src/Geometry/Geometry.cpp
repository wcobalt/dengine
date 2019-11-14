//
// Created by wcobalt on 3/30/19.
//

#include <cmath>

#include "Geometry.h"
#include "vectors.h"

using namespace dengine;

double Geometry::getDistance(const vec3f &from, const vec3f &to) {
    return (from - to).getModulo();
}

double Geometry::getDistance(const vec2f &from, const vec2f &to) {
    return (from - to).getModulo();
}

double Geometry::getAngle(const vec3f &a, const vec3f &b, double error) {
    return calculateAngle(a, b, error);
}

double Geometry::getAngle(const vec2f &a, const vec2f &b, double error) {
    return calculateAngle(a, b, error);
}

template<typename T>
double Geometry::calculateAngle(const T &a, const T &b, double error) {
    double modulusMultiplication = a.getModulo() * b.getModulo();
    double scalarWithB = a.scalar(b);
    int signOfScalar = scalarWithB < 0 ? -1 : 1;
    double absOfSubtraction = fabs(fabs(scalarWithB) / modulusMultiplication);

    if (fabs(absOfSubtraction - 1) < error) return acos(signOfScalar);
    else if (fabs(absOfSubtraction) < error) return acos(0);
    else return acos(scalarWithB / modulusMultiplication);
}


