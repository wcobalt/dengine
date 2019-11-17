//
// Created by wcobalt on 11/16/19.
//

#ifndef DENGINE_EULER_H
#define DENGINE_EULER_H

namespace dengine {
    template<typename T>
    class Vector3;

    template<typename T>
    class Vector2;
}

namespace dengine {
    class Euler {
    public:
        enum class Scheme {
            XYZ, XZY, YXZ, YZX, ZXY, ZYX
        };

        static double degreesToRadians(double degrees);

        static double radiansToDegrees(double radians);

        static double rad(int denominator);

        static double rad(int denominator, int coefficient);

        template<typename T>
        static Vector3<T> fromDegrees(T xRotation, T yRotation, T zRotation) {
            return {degreesToRadians(xRotation), degreesToRadians(yRotation), degreesToRadians(zRotation)};
        }
    };
}

#endif //DENGINE_EULER_H
