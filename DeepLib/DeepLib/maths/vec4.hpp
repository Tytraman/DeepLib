#ifndef DEEP_LIB_VEC4_HPP
#define DEEP_LIB_VEC4_HPP

#include "DeepCore/types.hpp"

#include <cmath>

namespace deep
{
    template <typename Type>
    struct vec4
    {
        Type x, y, z, w;

        vec4() = default;
        constexpr vec4(Type x, Type y, Type z, Type w) noexcept;

        constexpr bool operator==(const vec4<Type> &other) const noexcept;
        constexpr bool operator!=(const vec4<Type> &other) const noexcept;

        constexpr vec4<Type> operator-(Type value) const noexcept;
        constexpr vec4<Type> operator-(const vec4<Type> &other) const noexcept;
        constexpr vec4<Type> operator-() const noexcept;

        constexpr vec4<Type> &operator-=(Type value) noexcept;
        constexpr vec4<Type> &operator-=(const vec4<Type> &other) noexcept;

        constexpr vec4<Type> operator+(Type value) const noexcept;
        constexpr vec4<Type> operator+(const vec4<Type> &other) const noexcept;

        constexpr vec4<Type> &operator+=(Type value) noexcept;
        constexpr vec4<Type> &operator+=(const vec4<Type> &other) noexcept;

        constexpr vec4<Type> operator*(Type value) const noexcept;

        constexpr vec4<Type> &operator*=(Type value) noexcept;

        constexpr vec4<Type> operator/(Type value) const noexcept;

        constexpr vec4<Type> &operator/=(Type value) noexcept;

        static constexpr vec4<Type> sub(const vec4<Type> &vec, Type value) noexcept;
        static constexpr vec4<Type> sub(const vec4<Type> &vec1, const vec4<Type> &vec2) noexcept;

        static constexpr vec4<Type> add(const vec4<Type> &vec, Type value) noexcept;
        static constexpr vec4<Type> add(const vec4<Type> &vec1, const vec4<Type> &vec2) noexcept;

        static constexpr vec4<Type> mul(const vec4<Type> &vec, Type value) noexcept;

        static constexpr vec4<Type> div(const vec4<Type> &vec, Type value) noexcept;

        static constexpr vec4<Type> scale(const vec4<Type> &vec, Type scalar) noexcept;
        static constexpr Type magn(const vec4<Type> &vec) noexcept;
        /**
         * @brief Le vecteur ne doit pas être nul (composants à 0).
         * @param vec
         * @return
         */
        static constexpr vec4<Type> norm(const vec4<Type> &vec) noexcept;
        static constexpr Type dot(const vec4<Type> &vec1, const vec4<Type> &vec2) noexcept;
        static constexpr vec4<Type> inv(const vec4<Type> &vec) noexcept;
        // La fonction 'cross' n'a mathématiquement pas de représentation, c'est une exclusivité pour les vecteurs à 3 et 7 composants.
    };

    template <typename Type>
    inline constexpr vec4<Type>::vec4(Type _x, Type _y, Type _z, Type _w) noexcept
            : x(_x), y(_y), z(_z), w(_w)
    {
    }

    template <typename Type>
    inline constexpr bool vec4<Type>::operator==(const vec4<Type> &other) const noexcept
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    template <typename Type>
    inline constexpr bool vec4<Type>::operator!=(const vec4<Type> &other) const noexcept
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    template <typename Type>
    inline vec4<Type> vec4<Type>::operator-() const noexcept
    {
        return inv(*this);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::operator-(Type value) const noexcept
    {
        return sub(*this, value);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::operator-(const vec4<Type> &other) const noexcept
    {
        return sub(*this, other);
    }

    template <typename Type>
    inline constexpr vec4<Type> &vec4<Type>::operator-=(Type value) noexcept
    {
        *this = sub(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec4<Type> &vec4<Type>::operator-=(const vec4<Type> &other) noexcept
    {
        *this = sub(*this, other);

        return *this;
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::operator+(Type value) const noexcept
    {
        return add(*this, value);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::operator+(const vec4<Type> &other) const noexcept
    {
        return add(*this, other);
    }

    template <typename Type>
    inline constexpr vec4<Type> &vec4<Type>::operator+=(Type value) noexcept
    {
        *this = add(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec4<Type> &vec4<Type>::operator+=(const vec4<Type> &other) noexcept
    {
        *this = add(*this, other);

        return *this;
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::operator*(Type value) const noexcept
    {
        return mul(*this, value);
    }

    template <typename Type>
    inline constexpr vec4<Type> &vec4<Type>::operator*=(Type value) noexcept
    {
        *this = mul(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::operator/(Type value) const noexcept
    {
        return div(*this, value);
    }

    template <typename Type>
    inline constexpr vec4<Type> &vec4<Type>::operator/=(Type value) noexcept
    {
        *this = div(*this, value);

        return *this;
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::sub(const vec4<Type> &vec, Type value) noexcept
    {
        return vec4<Type>(
                vec.x - value,
                vec.y - value,
                vec.z - value,
                vec.w - value);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::sub(const vec4<Type> &vec1, const vec4<Type> &vec2) noexcept
    {
        return vec4<Type>(
                vec1.x - vec2.x,
                vec1.y - vec2.y,
                vec1.z - vec2.z,
                vec1.w - vec2.w);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::add(const vec4<Type> &vec, Type value) noexcept
    {
        return vec4<Type>(
                vec.x + value,
                vec.y + value,
                vec.z + value,
                vec.w + value);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::add(const vec4<Type> &vec1, const vec4<Type> &vec2) noexcept
    {
        return vec4<Type>(
                vec1.x + vec2.x,
                vec1.y + vec2.y,
                vec1.z + vec2.z,
                vec1.w + vec2.w);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::mul(const vec4<Type> &vec, Type value) noexcept
    {
        return vec4<Type>(
                vec.x * value,
                vec.y * value,
                vec.z * value,
                vec.w * value);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::div(const vec4<Type> &vec, Type value) noexcept
    {
        return vec4<Type>(
                vec.x / value,
                vec.y / value,
                vec.z / value,
                vec.w / value);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::scale(const vec4<Type> &vec, Type scalar) noexcept
    {
        return mul(vec, scalar);
    }

    template <typename Type>
    inline constexpr Type vec4<Type>::magn(const vec4<Type> &vec) noexcept
    {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::norm(const vec4<Type> &vec) noexcept
    {
        Type length = magn(vec);

        return vec4<Type>(
                static_cast<Type>(vec.x / length),
                static_cast<Type>(vec.y / length),
                static_cast<Type>(vec.z / length),
                static_cast<Type>(vec.w / length));
    }

    template <typename Type>
    inline constexpr Type vec4<Type>::dot(const vec4<Type> &vec1, const vec4<Type> &vec2) noexcept
    {
        return vec1.x * vec2.x +
               vec1.y * vec2.y +
               vec1.z * vec2.z +
               vec1.w * vec2.w;
    }

    template <typename Type>
    inline constexpr vec4<Type> vec4<Type>::inv(const vec4<Type> &vec) noexcept
    {
        return vec4<Type>(-vec.x, -vec.y, -vec.z, -vec.w);
    }
} // namespace deep

#endif
