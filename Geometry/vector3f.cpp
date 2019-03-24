//
// Created by wcobalt on 3/23/19.
//

#include "vector3f.h"
#include <cmath>

using namespace dengine::geometry;

vector3f::vector3f() {
    x = y = z = 0;
}

vector3f::vector3f(dengine::geometry::vector3f &vec) {
    *this = vec;
}

vector3f::vector3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float vector3f::getModule() {
    return std::sqrt(x * x + y * y + z * z);
}

void vector3f::normalize() {
    float module = getModule();

    x /= module;
    y /= module;
    z /= module;
}

vector3f vector3f::getNormalizedVector() {
    vector3f result(*this);

    result.normalize();

    return result;
}

vector3f& vector3f::operator=(vector3f b) {
    x = b.x;
    y = b.y;
    z = b.z;

    return *this;
}

vector3f vector3f::operator+(vector3f b) {
    vector3f result(*this);

    result.x += b.x;
    result.y += b.y;
    result.z += b.z;

    return result;
}

vector3f vector3f::operator-(vector3f b) {
    vector3f result(*this);

    result.x -= b.x;
    result.y -= b.y;
    result.z -= b.z;

    return result;
}

vector3f vector3f::operator-() {
    vector3f result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}