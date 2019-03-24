//
// Created by wcobalt on 3/23/19.
//

#include "vector2f.h"

using namespace dengine::geometry;

vector2f::vector2f():vector3f() {}

vector2f::vector2f(vector2f &vec):vector3f(vec) {
    z = 0;
}

vector2f::vector2f(float x, float y):vector3f(x, y, 0) {

}

vector2f vector2f::getNormalizedVector() {
    vector2f result(*this);

    result.normalize();

    return result;
}

vector2f& vector2f::operator=(vector2f b) {
    x = b.x;
    y = b.y;
}

vector2f vector2f::operator+(vector2f b) {
    vector2f result(*this);

    result.x += b.x;
    result.y += b.y;

    return result;
}

vector2f vector2f::operator-(vector2f b) {
    vector2f result(*this);

    result.x -= b.x;
    result.y -= b.y;

    return result;
}

vector2f vector2f::operator-() {
    vector2f result(*this);

    result.x = -x;
    result.y = -y;

    return result;
}