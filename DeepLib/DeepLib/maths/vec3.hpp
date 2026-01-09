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
        constexpr vec3(Type x, Type y, Type z) noexcept;

        constexpr bool operator==(const vec3 &other) const noexcept;
        constexpr bool operator!=(const vec3 &other) const noexcept;

        constexpr vec3 operator-(Type value) const noexcept;
        constexpr vec3 operator-(const vec3 &vec) const noexcept;

        constexpr vec3 &operator-=(Type value) noexcept;
        constexpr vec3 &operator-=(const vec3 &vec) noexcept;

        constexpr vec3 operator+(Type value) const noexcept;
        constexpr vec3 operator+(const vec3 &vec) const noexcept;

        constexpr vec3 &operator+=(Type value) noexcept;
        constexpr vec3 &operator+=(const vec3 &vec) noexcept;

        constexpr vec3 operator*(Type value) const noexcept;

        constexpr vec3 &operator*=(const Type &value) noexcept;

        constexpr vec3 operator/(const Type &value) const noexcept;

        constexpr vec3 &operator/=(const Type &value) noexcept;

        constexpr vec3 xyz() const noexcept;
        constexpr vec3 xzy() const noexcept;
        constexpr vec3 yxz() const noexcept;
        constexpr vec3 yzx() const noexcept;
        constexpr vec3 zxy() const noexcept;
        constexpr vec3 zyx() const noexcept;

        static constexpr vec3 sub(const vec3 &vec, Type value) noexcept;
        static constexpr vec3 sub(const vec3 &vec1, const vec3 &vec2) noexcept;

        static constexpr vec3 add(const vec3 &vec, Type value) noexcept;
        static constexpr vec3 add(const vec3 &vec1, const vec3 &vec2) noexcept;

        static constexpr vec3 mul(const vec3 &vec, Type value) noexcept;

        static constexpr vec3 div(const vec3 &vec, Type value) noexcept;

        static constexpr vec3 scale(const vec3 &vec, const Type &scalar) noexcept;
        static constexpr float magn(const vec3 &vec) noexcept;
        static constexpr vec3 norm(const vec3 &vec) noexcept;
        static constexpr vec3 cross(const vec3 &vec1, const vec3 &vec2) noexcept;
        static constexpr Type dot(const vec3 &vec1, const vec3 &vec2) noexcept;
        static constexpr vec3 inv(const vec3 &vec) noexcept;
    };

    template <typename Type>
    inline constexpr vec3<Type>::vec3(Type _x, Type _y, Type _z) noexcept
            : x(_x), y(_y), z(_z)
    {
    }

    template <typename Type>
    inline constexpr bool vec3<Type>::operator==(const vec3 &other) const noexcept
    {
        return x == other.x && y == other.y && z == other.z;
    }

    template <typename Type>
    inline constexpr bool vec3<Type>::operator!=(const vec3 &other) const noexcept
    {
        return x != other.x || y != other.y || z != other.z;
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::operator-(Type value) const noexcept
    {
        return sub(*this, value);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::operator-(const vec3 &vec) const noexcept
    {
        return sub(*this, vec);
    }

    template <typename Type>
    inline constexpr vec3<Type> &vec3<Type>::operator-=(Type value) noexcept
    {
        *this = sub(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec3<Type> &vec3<Type>::operator-=(const vec3 &vec) noexcept
    {
        *this = sub(*this, vec);

        return *this;
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::operator+(Type value) const noexcept
    {
        return add(*this, value);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::operator+(const vec3 &vec) const noexcept
    {
        return add(*this, vec);
    }

    template <typename Type>
    inline constexpr vec3<Type> &vec3<Type>::operator+=(Type value) noexcept
    {
        *this = add(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec3<Type> &vec3<Type>::operator+=(const vec3 &vec) noexcept
    {
        *this = add(*this, vec);

        return *this;
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::operator*(Type value) const noexcept
    {
        return mul(*this, value);
    }

    template <typename Type>
    inline constexpr vec3<Type> &vec3<Type>::operator*=(const Type &value) noexcept
    {
        *this = mul(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::operator/(const Type &value) const noexcept
    {
        return div(*this, value);
    }

    template <typename Type>
    inline constexpr vec3<Type> &vec3<Type>::operator/=(const Type &value) noexcept
    {
        *this = div(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::xyz() const noexcept
    {
        return vec3<Type>(x, y, z);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::xzy() const noexcept
    {
        return vec3<Type>(x, z, y);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::yxz() const noexcept
    {
        return vec3<Type>(y, x, z);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::yzx() const noexcept
    {
        return vec3<Type>(y, z, x);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::zxy() const noexcept
    {
        return vec3<Type>(z, x, y);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::zyx() const noexcept
    {
        return vec3<Type>(z, y, x);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::sub(const vec3 &vec, Type value) noexcept
    {
        return vec3<Type>(
                vec.x - value,
                vec.y - value,
                vec.z - value);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::sub(const vec3 &vec1, const vec3 &vec2) noexcept
    {
        return vec3<Type>(
                vec1.x - vec2.x,
                vec1.y - vec2.y,
                vec1.z - vec2.z);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::add(const vec3 &vec, Type value) noexcept
    {
        return vec3<Type>(
                vec.x + value,
                vec.y + value,
                vec.z + value);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::add(const vec3 &vec1, const vec3 &vec2) noexcept
    {
        return vec3<Type>(
                vec1.x + vec2.x,
                vec1.y + vec2.y,
                vec1.z + vec2.z);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::mul(const vec3 &vec, Type value) noexcept
    {
        return vec3<Type>(
                vec.x * value,
                vec.y * value,
                vec.z * value);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::div(const vec3 &vec, Type value) noexcept
    {
        return vec3<Type>(
                vec.x / value,
                vec.y / value,
                vec.z / value);
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::scale(const vec3 &vec, const Type &scalar) noexcept
    {
        return vec3<Type>(
                vec.x * scalar,
                vec.y * scalar,
                vec.z * scalar);
    }

    template <typename Type>
    inline constexpr float vec3<Type>::magn(const vec3 &vec) noexcept
    {
        return std::sqrtf(static_cast<float>(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::norm(const vec3 &vec) noexcept
    {
        float length = magn(vec);

        return vec3<Type>(
                static_cast<Type>(vec.x / length),
                static_cast<Type>(vec.y / length),
                static_cast<Type>(vec.z / length));
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::cross(const vec3 &vec1, const vec3 &vec2) noexcept
    {
        return vec3<Type>(
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x);
    }

    template <typename Type>
    inline constexpr Type vec3<Type>::dot(const vec3 &vec1, const vec3 &vec2) noexcept
    {
        return vec1.x * vec2.x +
               vec1.y * vec2.y +
               vec1.z * vec2.z;
    }

    template <typename Type>
    inline constexpr vec3<Type> vec3<Type>::inv(const vec3 &vec) noexcept
    {
        return scale(vec, static_cast<Type>(-1));
    }
} // namespace deep

#endif
