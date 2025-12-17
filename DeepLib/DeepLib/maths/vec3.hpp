#ifndef DEEP_LIB_VEC3_HPP
#define DEEP_LIB_VEC3_HPP

#include "DeepCore/types.hpp"

#include <cmath>

namespace deep
{
    template <typename Type>
    struct vec3
    {
        Type x, y, z;

        vec3() = default;
        constexpr vec3(const Type &x, const Type &y, const Type &z);

        bool operator==(const vec3 &other) const;
        bool operator!=(const vec3 &other) const;

        vec3 operator-(const Type &value) const;
        vec3 operator-(const vec3 &vec) const;

        vec3 &operator-=(const Type &value);
        vec3 &operator-=(const vec3 &vec);

        vec3 operator+(const Type &value) const;
        vec3 operator+(const vec3 &vec) const;

        vec3 &operator+=(const Type &value);
        vec3 &operator+=(const vec3 &vec);

        vec3 operator*(const Type &value) const;

        vec3 &operator*=(const Type &value);

        vec3 operator/(const Type &value) const;

        vec3 &operator/=(const Type &value);

        vec3 xyz() const;
        vec3 xzy() const;
        vec3 yxz() const;
        vec3 yzx() const;
        vec3 zxy() const;
        vec3 zyx() const;

        static vec3 sub(const vec3 &vec, const Type &value);
        static vec3 sub(const vec3 &vec1, const vec3 &vec2);

        static vec3 add(const vec3 &vec, const Type &value);
        static vec3 add(const vec3 &vec1, const vec3 &vec2);

        static vec3 mul(const vec3 &vec, const Type &value);

        static vec3 div(const vec3 &vec, const Type &value);

        static vec3 scale(const vec3 &vec, const Type &scalar);
        static float magn(const vec3 &vec);
        static vec3 norm(const vec3 &vec);
        static vec3 cross(const vec3 &vec1, const vec3 &vec2);
        static float dot(const vec3 &vec1, const vec3 &vec2);
        static vec3 inv(const vec3 &vec);
    };

    template <typename Type>
    inline constexpr vec3<Type>::vec3(const Type &_x, const Type &_y, const Type &_z)
            : x(_x), y(_y), z(_z)
    {
    }

    template <typename Type>
    inline bool vec3<Type>::operator==(const vec3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    template <typename Type>
    inline bool vec3<Type>::operator!=(const vec3 &other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::operator-(const Type &value) const
    {
        return sub(*this, value);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::operator-(const vec3 &vec) const
    {
        return sub(*this, vec);
    }

    template <typename Type>
    inline vec3<Type> &vec3<Type>::operator-=(const Type &value)
    {
        *this = sub(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec3<Type> &vec3<Type>::operator-=(const vec3 &vec)
    {
        *this = sub(*this, vec);

        return *this;
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::operator+(const Type &value) const
    {
        return add(*this, value);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::operator+(const vec3 &vec) const
    {
        return add(*this, vec);
    }

    template <typename Type>
    inline vec3<Type> &vec3<Type>::operator+=(const Type &value)
    {
        *this = add(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec3<Type> &vec3<Type>::operator+=(const vec3 &vec)
    {
        *this = add(*this, vec);

        return *this;
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::operator*(const Type &value) const
    {
        return mul(*this, value);
    }

    template <typename Type>
    inline vec3<Type> &vec3<Type>::operator*=(const Type &value)
    {
        *this = mul(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::operator/(const Type &value) const
    {
        return div(*this, value);
    }

    template <typename Type>
    inline vec3<Type> &vec3<Type>::operator/=(const Type &value)
    {
        *this = div(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::xyz() const
    {
        return vec3<Type>(x, y, z);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::xzy() const
    {
        return vec3<Type>(x, z, y);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::yxz() const
    {
        return vec3<Type>(y, x, z);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::yzx() const
    {
        return vec3<Type>(y, z, x);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::zxy() const
    {
        return vec3<Type>(z, x, y);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::zyx() const
    {
        return vec3<Type>(z, y, x);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::sub(const vec3 &vec, const Type &value)
    {
        return vec3<Type>(
                vec.x - value,
                vec.y - value,
                vec.z - value);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::sub(const vec3 &vec1, const vec3 &vec2)
    {
        return vec3<Type>(
                vec1.x - vec2.x,
                vec1.y - vec2.y,
                vec1.z - vec2.z);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::add(const vec3 &vec, const Type &value)
    {
        return vec3<Type>(
                vec.x + value,
                vec.y + value,
                vec.z + value);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::add(const vec3 &vec1, const vec3 &vec2)
    {
        return vec3<Type>(
                vec1.x + vec2.x,
                vec1.y + vec2.y,
                vec1.z + vec2.z);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::mul(const vec3 &vec, const Type &value)
    {
        return vec3<Type>(
                vec.x * value,
                vec.y * value,
                vec.z * value);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::div(const vec3 &vec, const Type &value)
    {
        return vec3<Type>(
                vec.x / value,
                vec.y / value,
                vec.z / value);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::scale(const vec3 &vec, const Type &scalar)
    {
        return vec3<Type>(
                vec.x * scalar,
                vec.y * scalar,
                vec.z * scalar);
    }

    template <typename Type>
    inline float vec3<Type>::magn(const vec3 &vec)
    {
        return std::sqrtf(static_cast<float>(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::norm(const vec3 &vec)
    {
        float length = magn(vec);

        return vec3<Type>(
                static_cast<Type>(vec.x / length),
                static_cast<Type>(vec.y / length),
                static_cast<Type>(vec.z / length));
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::cross(const vec3 &vec1, const vec3 &vec2)
    {
        return vec3<Type>(
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x);
    }

    template <typename Type>
    inline float vec3<Type>::dot(const vec3 &vec1, const vec3 &vec2)
    {
        return static_cast<float>(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
    }

    template <typename Type>
    inline vec3<Type> vec3<Type>::inv(const vec3 &vec)
    {
        return scale(vec, static_cast<Type>(-1));
    }
} // namespace deep

#endif
