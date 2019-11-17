//
// Created by wcobalt on 3/30/19.
//

#ifndef DENGINE_GEOMETRY_H
#define DENGINE_GEOMETRY_H

namespace dengine {
    template<typename T>
    class Vector3;

    template<typename T>
    class Vector2;

    using vec3f = Vector3<float>;
    using vec2f = Vector2<float>;
}

namespace dengine {
    class Geometry {
    private:
        template<typename T>
        static double calculateAngle(const T &a, const T &b);
    public:
        static double getDistance(const vec3f &from, const vec3f &to);

        static double getDistance(const vec2f &from, const vec2f &to);

        static double getAngle(const vec3f &a, const vec3f &b);

        static double getAngle(const vec2f &a, const vec2f &b);
    };
}

#endif //DENGINE_GEOMETRY_H
