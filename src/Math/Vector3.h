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

        Vector3() : x(0), y(0), z(0) {}

        Vector3(const Vector2<T>& vector, T z = 0) : x(vector.x), y(vector.y), z(z) {}

        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        Vector3(const std::vector<T>& vector) : Vector3() {
            size_t size = vector.size();

            if (size > 0) {
                x = vector[0];

                if (size > 1) {
                    y = vector[1];

                    if (size > 2)
                        z = vector[2];
                }
            }
        }

        inline T getModulo() const override {
            return std::sqrt(x * x + y * y + z * z);
        }

        void normalize() override {
            T modulo = getModulo();

            *this /= modulo;
        }

        Vector3<T> getNormalizedVector() const {
            Vector3<T> temp = *this;

            temp.normalize();

            return temp;
        }

        std::vector<T> toStlVector() const override {
            return {x, y, z};
        }

        T scalar(const Vector3<T>& b) const {
            return x * b.x + y * b.y + z * b.z;
        }

        bool operator==(const Vector3<T>& b) const {
            return (x == b.x) && (y == b.y) && (z == b.z);
        }

        bool equals(const Vector3<T>& b, T error) const {
            return Number::equals(x, b.x, error) && Number::equals(y, b.y, error) && Number::equals(z, b.z, error);
        }

        double getAngle(const Vector3<T>& b) const {
            return Geometry::getAngle(*this, b);
        }

        Vector3<T> operator*(const Vector3<T>& b) const {
            Vector3<T> result;

            result.x = y * b.z - b.y * z;
            result.y = b.x * z - x * b.z;
            result.z = x * b.y - b.x * y;

            return result;
        }

        Vector3<T>& operator*=(const Vector3<T>& b) {
            return *this = *this * b;
        }

        Vector3<T>& operator+=(const Vector3<T>& b) {
            return *this = *this + b;
        }

        Vector3<T> operator+(const Vector3<T>& b) const {
            Vector3<T> result = *this;

            result.x += b.x;
            result.y += b.y;
            result.z += b.z;

            return result;
        }

        Vector3<T>& operator-=(const Vector3<T>& b) {
            return *this = *this - b;
        }

        Vector3<T> operator-(const Vector3<T>& b) const {
            Vector3<T> result = *this;

            result.x -= b.x;
            result.y -= b.y;
            result.z -= b.z;

            return result;
        }

        Vector3<T> operator-() const {
            Vector3<T> result;

            result.x = -x;
            result.y = -y;
            result.z = -z;

            return result;
        }

        Vector3<T>& operator*=(T b) {
            return *this = *this * b;
        }

        Vector3<T> operator*(T b) const {
            Vector3<T> result = *this;

            result.x *= b;
            result.y *= b;
            result.z *= b;

            return result;
        }

        Vector3<T>& operator/=(T b) {
            return *this = *this / b;
        }

        Vector3<T> operator/(T b) const {
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
    Vector3<T> operator*(T a, const Vector3<T>& b) {
        return b * a;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vector) {
        return stream << vector.toString();
    }
}

#endif //DENGINE_VECTOR3_H
