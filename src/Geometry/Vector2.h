//
// Created by wcobalt on 3/23/19.
//

#include <vector>
#include <cmath>

#ifndef DENGINE_VECTOR2_H
#define DENGINE_VECTOR2_H

namespace dengine {
    template <typename T> class Vector3;
}

#include "Vector.h"
#include "Geometry.h"

namespace dengine {
    template <typename T>
    class Vector2 : public Vector<T> {
    public:
        T x, y;

        inline Vector2() : x(0), y(0) {}

        inline Vector2(const Vector2<T>& vector) = default;

        inline Vector2(const Vector3<T>& vector) : x(vector.x), y(vector.y) {}

        inline Vector2(T x, T y) : x(x), y(y) {}

        inline Vector2(const std::vector<T>& vector) : Vector2() {
            size_t size = vector.size();

            if (size > 0) x = vector[0];
            if (size > 1) y = vector[1];
        }

        inline T getModulo() const override {
            return sqrt(x * x + y * y);
        }

        inline void normalize() override {
            T modulo = getModulo();

            *this /= modulo;
        }

        inline Vector2<T> getNormalizedVector() const {
            Vector2<T> temp = *this;

            temp.normalize();

            return temp;
        }

        inline std::vector<T> toStlVector() const override {
            return {x, y};
        }

        inline Vector2<T>& operator=(const Vector2<T>& b) = default;

        inline T scalar(const Vector2<T>& b) const {
            return x * b.x + y * b.y;
        }

        inline bool operator==(const Vector2<T>& b) const {
            return x == b.x && y == b.y;
        }

        inline bool equals(const Vector2<T>& b, T error) const {
            return abs(x - b.x) <= error && abs(y - b.y) <= error;
        }

        inline double getAngle(const Vector2<T>& b) const {
            return acos(scalar(b) / (getModulo() * b.getModulo()));
        }

        inline double getAngleAuto(const Vector2<T>& b) const {
            return getAngle(b, Vector<T>::AUTO_ANGLE_CALC_PRECISION);
        }

        inline double getAngle(const Vector2<T>& b, double error) const {
            return Geometry::getAngle(*this, b, error);
        }

        inline Vector2<T>& operator+=(const Vector2<T>& b) {
            return *this = *this + b;
        }

        inline Vector2<T> operator+(const Vector2<T>& b) const {
            Vector2<T> result = *this;

            result.x += b.x;
            result.y += b.y;

            return result;
        }

        inline Vector2<T>& operator-=(const Vector2<T>& b) {
            return *this = *this - b;
        }

        inline Vector2<T> operator-(const Vector2<T>& b) const {
            return *this + -b;
        }

        inline Vector2<T> operator-() const {
            Vector2<T> result = *this;

            result *= static_cast<T>(-1);

            return result;
        }

        inline Vector2<T>& operator*=(T b) {
            return *this = *this * b;
        }

        inline Vector2<T> operator*(T b) const {
            Vector2<T> result = *this;

            result.x *= b;
            result.y *= b;

            return result;
        }

        inline Vector2<T>& operator/=(T b) {
            return *this = *this / b;
        }

        inline Vector2<T> operator/(T b) const {
            Vector2<T> result = *this;

            result.x /= b;
            result.y /= b;

            return result;
        }

        std::string toString() const override {
            return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }
    };

    template<typename T>
    inline Vector2<T> operator*(T a, const Vector2<T>& b) {
        return b * a;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector) {
        return stream << vector.toString();
    }
}

#endif //DENGINE_VECTOR2_H