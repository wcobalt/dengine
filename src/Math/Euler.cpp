//
// Created by wcobalt on 11/16/19.
//
#include <cmath>
#include "Euler.h"

using namespace dengine;

double Euler::degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double Euler::radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

double Euler::rad(int denominator) {
    return rad(denominator, 1);
}

double Euler::rad(int denominator, int coefficient) {
    return coefficient * M_PI / denominator;
}

