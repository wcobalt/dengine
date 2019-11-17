//
// Created by wcobalt on 11/15/19.
//
#include <cmath>

#ifndef DENGINE_NUMBER_H
#define DENGINE_NUMBER_H

namespace dengine {
    class Number {
    public:
        template<typename T, typename V>
        static bool equals(T a, T b, V error) {
            return abs(a - b) < error;
        }

        static bool equals(double a, double b, double error) {
            return fabs(a - b) < error;
        }

        static bool equals(float a, float b, float error) {
            return equals((double)a, (double)b, (double)error);
        }
    };
}

#endif //DENGINE_NUMBER_H
