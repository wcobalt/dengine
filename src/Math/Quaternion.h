//
// Created by wcobalt on 11/16/19.
//
#include <cmath>

#ifndef DENGINE_QUATERNION_H
#define DENGINE_QUATERNION_H

namespace dengine {
    template<typename T>
    class Vector3;
}

#include "../DObject.h"
#include "Number.h"
#include "Euler.h"

namespace dengine {
    template<typename T>
    class Quaternion : public virtual DObject {
    private:
        using EulerScheme = Euler::Scheme;

        T mScalar;
        Vector3<T> vector;

        template<typename FT>
        friend Quaternion<FT> operator*(FT a, const Quaternion<FT>& b);

        template<typename FT>
        friend Vector3<FT> operator*(const Vector3<FT>& a, const Quaternion<FT>& b);

        template<typename FT>
        friend std::ostream& operator<<(std::ostream& stream, const Quaternion<FT>& quaternion);
    public:
        Quaternion() : vector(), mScalar(0) {}

        Quaternion(T x, T y, T z, T w) : mScalar(w), vector(x, y, z) {}

        Quaternion(T eulerX, T eulerY, T eulerZ) : Quaternion(eulerX, eulerY, eulerZ, EulerScheme::XYZ) {}

        Quaternion(const std::vector<T>& stlVector) : Quaternion() {
            vector = Vector3<T>(stlVector);

            if (stlVector.size() > 3) mScalar = stlVector[3];
        }

        Quaternion(T eulerX, T eulerY, T eulerZ, EulerScheme scheme) {
            Quaternion<T> xRotation = axisRotation({1, 0, 0}, eulerX);
            Quaternion<T> yRotation = axisRotation({0, 1, 0}, eulerY);
            Quaternion<T> zRotation = axisRotation({0, 0, 1}, eulerZ);

            switch (scheme) {
                case EulerScheme::XYZ:
                    *this = zRotation * yRotation * xRotation;

                    break;

                case EulerScheme::XZY:
                    *this = yRotation * zRotation * xRotation;

                    break;

                case EulerScheme::YXZ:
                    *this = zRotation * xRotation * yRotation;

                    break;

                case EulerScheme::YZX:
                    *this = xRotation * zRotation * yRotation;

                    break;

                case EulerScheme::ZXY:
                    *this = yRotation * xRotation * zRotation;

                    break;

                case EulerScheme::ZYX:
                    *this = xRotation * yRotation * zRotation;

                    break;
            }
        }

        explicit Quaternion(const Vector3<T>& eulerAngles) : Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z) {}

        Quaternion(const Vector3<T>& vector, T scalar) : Quaternion(vector.x, vector.y, vector.z, scalar) {}

        bool operator==(const Quaternion<T>& b) const {
            return (vector == b.vector) && (mScalar == b.mScalar);
        }

        bool equals(const Quaternion<T>& b, T error) const {
            return vector.equals(b.vector, error) && Number::equals(mScalar, b.mScalar, error);
        }

        template<typename MT>
        static Quaternion<MT> axisRotation(const Vector3<MT>& vector, MT euler) {
            Quaternion<MT> result;

            result.mScalar = std::cos(euler / 2);
            result.vector = std::sin(euler / 2) * vector;

            return result;
        }

        Quaternion<T> operator+(const Quaternion<T>& b) const {
            Quaternion<T> result = *this;

            result.mScalar += b.mScalar;
            result.vector += b.vector;

            return result;
        }

        Quaternion<T>& operator+=(const Quaternion<T>& b) const {
            *this = *this + b;
        }

        Quaternion<T> operator-(const Quaternion<T>& b) const {
            Quaternion<T> result = *this;

            result.mScalar -= b.mScalar;
            result.vector -= b.vector;

            return result;
        }

        Quaternion<T>& operator-=(const Quaternion<T>& b) const {
            *this = *this - b;
        }

        Quaternion<T> operator*(const Quaternion<T>& b) const {
            Quaternion<T> result;

            result.mScalar = mScalar * b.mScalar - vector.scalar(b.vector);
            result.vector = mScalar * b.vector + b.mScalar * vector + vector * b.vector;

            return result;
        }

        Quaternion<T>& operator*=(const Quaternion<T>& b) const {
            *this = *this * b;
        }

        Quaternion<T> operator*(T b) const {
            Quaternion<T> result = *this;

            result.mScalar *= b;
            result.vector *= b;

            return result;
        }

        Quaternion<T>& operator*=(T b) const {
            *this = *this * b;
        }

        Vector3<T> operator*(const Vector3<T>& b) const {
            return (*this * Quaternion(b, 0) * getReciprocal()).getVector();
        }

        Quaternion<T>& operator*=(const Vector3<T>& b) const {
            *this = *this * b;
        }

        Quaternion<T> operator/(T b) const {
            Quaternion<T> result = *this;

            result.mScalar /= b;
            result.vector /= b;

            return result;
        }

        Quaternion<T>& operator/=(T b) const {
            *this = *this / b;
        }

        Quaternion<T> multiply(const Vector3<T>& b) {
            return Quaternion(b, 0) * *this;
        }

        Quaternion<T>& multiplyAssign(const Vector3<T>& b) {
            return *this = Quaternion(b, 0) * *this;
        }

        Vector3<T> getVector() const {
            return vector;
        }

        T scalar(const Quaternion<T>& b) const {
            return vector * b.vector + mScalar * b.mScalar;
        }

        T getScalar() const {
            return mScalar;
        }

        void makeUnit() {
            *this /= getNorm();
        }

        Quaternion<T> getUnit() const {
            Quaternion<T> result = *this;

            result.makeUnit();

            return result;
        }

        void makeReciprocal() {
            T norm = getNorm();

            *this = getConjugation() / (norm * norm);
        }

        Quaternion<T> getReciprocal() const {
            Quaternion<T> result = *this;

            result.makeReciprocal();

            return result;
        }

        void makeConjugate() {
            vector *= -1;
        }

        Quaternion<T> getConjugation() const {
            Quaternion<T> result = *this;

            result.makeConjugate();

            return result;
        }

        T getNorm() const {
            return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + mScalar * mScalar);
        }

        Vector3<T> getEulerAngles() const {
            Vector3<T> result;

            T x = vector.x, y = vector.y, z = vector.z, w = mScalar;

            result.x = std::atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
            result.y = std::asin(2 * (w * y - z * x));
            result.z = std::atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));

            return result;
        }

        std::vector<T> toStlVector() const {
            return {vector.x, vector.y, vector.z, mScalar};
        }

        std::string toString() const override {
            return "Quat(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ", " +
                std::to_string(vector.z) + ", " + std::to_string(mScalar) + ")";
        }
    };

    template<typename T>
    Quaternion<T> operator*(T a, const Quaternion<T> &b) {
        return b * a;
    }

    template<typename T>
    Vector3<T> operator*(const Vector3<T>& a, const Quaternion<T>& b) {
        return b * a;
    }

    template<typename T>
    Vector3<T>& operator*=(Vector3<T>& a, const Quaternion<T>& b) {
        return a = a * b;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& quaternion) {
        return stream << quaternion.toString();
    }
}

#endif //DENGINE_QUATERNION_H
