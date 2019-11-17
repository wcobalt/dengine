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
#include "Number.h"

namespace dengine {
    template <typename T>
    class Vector2 : public Vector<T> {
    public:
        T x, y;

        Vector2() : x(0), y(0) {}

        Vector2(const Vector2<T>& vector) = default;

        Vector2(const Vector3<T>& vector) : x(vector.x), y(vector.y) {}

        Vector2(T x, T y) : x(x), y(y) {}

        Vector2(const std::vector<T>& vector) : Vector2() {
            size_t size = vector.size();

            if (size > 0) x = vector[0];
            if (size > 1) y = vector[1];
        }

        T getModulo() const override {
            return std::sqrt(x * x + y * y);
        }

        void normalize() override {
            T modulo = getModulo();

            *this /= modulo;
        }

        Vector2<T> getNormalizedVector() const {
            Vector2<T> temp = *this;

            temp.normalize();

            return temp;
        }

        std::vector<T> toStlVector() const override {
            return {x, y};
        }

        Vector2<T>& operator=(const Vector2<T>& b) = default;

        T scalar(const Vector2<T>& b) const {
            return x * b.x + y * b.y;
        }

        bool operator==(const Vector2<T>& b) const {
            return (x == b.x) && (y == b.y);
        }

        bool equals(const Vector2<T>& b, T error) const {
            return Number::equals(x, b.x, error) && Number::equals(y, b.y, error);
        }

        double getAngle(const Vector2<T>& b) const {
            return Geometry::getAngle(*this, b);
        }

        Vector2<T>& operator+=(const Vector2<T>& b) {
            return *this = *this + b;
        }

        Vector2<T> operator+(const Vector2<T>& b) const {
            Vector2<T> result = *this;

            result.x += b.x;
            result.y += b.y;

            return result;
        }

        Vector2<T>& operator-=(const Vector2<T>& b) {
            return *this = *this - b;
        }

        Vector2<T> operator-(const Vector2<T>& b) const {
            Vector2<T> result = *this;

            result.x -= b.x;
            result.y -= b.y;

            return result;
        }

        Vector2<T> operator-() const {
            Vector2<T> result;

            result.x = -x;
            result.y = -y;

            return result;
        }

        Vector2<T>& operator*=(T b) {
            return *this = *this * b;
        }

        Vector2<T> operator*(T b) const {
            Vector2<T> result = *this;

            result.x *= b;
            result.y *= b;

            return result;
        }

        Vector2<T>& operator/=(T b) {
            return *this = *this / b;
        }

        Vector2<T> operator/(T b) const {
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
    Vector2<T> operator*(T a, const Vector2<T>& b) {
        return b * a;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector) {
        return stream << vector.toString();
    }
}

#endif //DENGINE_VECTOR2_H