//
// Created by wcobalt on 3/23/19.
//

#include <vector>
#include <cmath>

#ifndef DENGINE_VECTOR3_H
#define DENGINE_VECTOR3_H

namespace dengine {
    template <class T> class Vector2;
    class Geometry;
}

#include "Vector.h"
#include "Geometry.h"

namespace dengine {
    template<typename T>
    class Vector3 : public Vector<T> {
    public:
        T x, y, z;

        inline Vector3() : x(0), y(0), z(0) {}

        inline Vector3(const Vector3<T>& vector) = default;

        inline Vector3(const Vector2<T>& vector) : x(vector.x), y(vector.y), z(0) {}

        inline Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        inline Vector3(const std::vector<T>& vector) : Vector3() {
            size_t size = vector.size();

            if (size > 0) x = vector[0];
            if (size > 1) y = vector[1];
            if (size > 2) z = vector[2];
        }

        inline T getModulo() const override {
            return sqrt(x * x + y * y + z * z);
        }

        inline void normalize() override {
            T modulo = getModulo();

            *this /= modulo;
        }

        inline Vector3<T> getNormalizedVector() const {
            Vector3<T> temp = *this;

            temp.normalize();

            return temp;
        }

        inline std::vector<T> toStlVector() const override {
            return {x, y, z};
        }

        inline Vector3<T>& operator=(const Vector3<T>& b) = default;

        inline T scalar(const Vector3<T>& b) const {
            return x * b.x + y * b.y + z * b.z;
        }

        inline bool operator==(const Vector3<T>& b) const {
            return x == b.x && y == b.y && z == b.z;
        }

        inline bool equals(const Vector3<T>& b, T error) const {
            return abs(x - b.x) <= error && abs(y - b.y) <= error && abs(z - b.z) <= error;
        }

        inline double getAngle(const Vector3<T>& b) const {
            return acos(scalar(b) / (getModulo() * b.getModulo()));
        }

        inline double getAngleAuto(const Vector3<T>& b) const {
            return getAngle(b, Vector<T>::AUTO_ANGLE_CALC_PRECISION);
        }

        inline double getAngle(const Vector3<T>& b, double error) const {
            return Geometry::getAngle(*this, b, error);
        }

        inline Vector3<T> operator*(const Vector3<T>& b) const {
            Vector3<T> result;

            result.x = y * b.z - b.y * z;
            result.y = b.x * z - x * b.z;
            result.z = x * b.y - b.x * y;

            return result;
        }

        inline Vector3<T>& operator*=(const Vector3<T>& b) {
            *this = *this * b;
        }

        inline Vector3<T>& operator+=(const Vector3<T>& b) {
            return *this = *this + b;
        }

        inline Vector3<T> operator+(const Vector3<T>& b) const {
            Vector3<T> result = *this;

            result.x += b.x;
            result.y += b.y;
            result.z += b.z;

            return result;
        }

        inline Vector3<T>& operator-=(const Vector3<T>& b) {
            return *this = *this - b;
        }

        inline Vector3<T> operator-(const Vector3<T>& b) const {
            return *this + -b;
        }

        inline Vector3<T> operator-() const {
            Vector3<T> result = *this;

            result *= static_cast<T>(-1);

            return result;
        }

        inline Vector3<T>& operator*=(T b) {
            return *this = *this * b;
        }

        inline Vector3<T> operator*(T b) const {
            Vector3<T> result = *this;

            result.x *= b;
            result.y *= b;
            result.z *= b;

            return result;
        }

        inline Vector3<T>& operator/=(T b) {
            return *this = *this / b;
        }

        inline Vector3<T> operator/(T b) const {
            Vector3<T> result = *this;

            result.x /= b;
            result.y /= b;
            result.z /= b;

            return result;
        }

        std::string toString() const override {
            return "Vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
        }
    };

    template<typename T>
    inline Vector3<T> operator*(T a, const Vector3<T>& b) {
        return b * a;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vector) {
        return stream << vector.toString();
    }
}

#endif //DENGINE_VECTOR3_H
