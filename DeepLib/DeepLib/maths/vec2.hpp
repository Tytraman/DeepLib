#ifndef DEEP_LIB_VEC2_HPP
#define DEEP_LIB_VEC2_HPP

#include "DeepCore/types.hpp"

#include <cmath>

namespace deep
{
    template <typename Type>
    struct vec2
    {
        Type x, y;

        vec2() = default;
        vec2(const Type &x, const Type &y);

        bool operator==(const vec2 &other) const;
        bool operator!=(const vec2 &other) const;

        vec2 operator-(const Type &value) const;
        vec2 operator-(const vec2 &vec) const;

        vec2 &operator-=(const Type &value);
        vec2 &operator-=(const vec2 &vec);

        vec2 operator+(const Type &value) const;
        vec2 operator+(const vec2 &vec) const;

        vec2 &operator+=(const Type &value);
        vec2 &operator+=(const vec2 &vec);

        vec2 operator*(const Type &value) const;

        vec2 &operator*=(const Type &value);

        vec2 operator/(const Type &value) const;

        vec2 &operator/=(const Type &value);

        vec2 xy() const;
        vec2 yx() const;

        float get_length() const;

        static vec2 sub(const vec2 &vec, const Type &value);
        static vec2 sub(const vec2 &vec1, const vec2 &vec2);

        static vec2 add(const vec2 &vec, const Type &value);
        static vec2 add(const vec2 &vec1, const vec2 &vec2);

        static vec2 mul(const vec2 &vec, const Type &value);

        static vec2 div(const vec2 &vec, const Type &value);

        static vec2 scale(const vec2 &v, const Type &scalar);
        static float magn(const vec2 &vec);
        static vec2 norm(const vec2 &vec);
        static float dot(const vec2 &vec1, const vec2 &vec2);
        static vec2 inv(const vec2 &vec);
    };

    template <typename Type>
    inline vec2<Type>::vec2(const Type &_x, const Type &_y)
            : x(_x), y(_y)
    {
    }

    template <typename Type>
    inline bool vec2<Type>::operator==(const vec2 &other) const
    {
        return x == other.x && y == other.y;
    }

    template <typename Type>
    inline bool vec2<Type>::operator!=(const vec2 &other) const
    {
        return x != other.x || y != other.y;
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::xy() const
    {
        return vec2(x, y);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::operator-(const Type &value) const
    {
        return sub(*this, value);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::operator-(const vec2 &vec) const
    {
        return sub(*this, vec);
    }

    template <typename Type>
    inline vec2<Type> &vec2<Type>::operator-=(const Type &value)
    {
        *this = sub(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec2<Type> &vec2<Type>::operator-=(const vec2 &vec)
    {
        *this = sub(*this, vec);

        return *this;
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::operator+(const Type &value) const
    {
        return add(*this, value);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::operator+(const vec2 &vec) const
    {
        return add(*this, vec);
    }

    template <typename Type>
    inline vec2<Type> &vec2<Type>::operator+=(const Type &value)
    {
        *this = add(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec2<Type> &vec2<Type>::operator+=(const vec2 &vec)
    {
        *this = add(*this, vec);

        return *this;
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::operator*(const Type &value) const
    {
        return mul(*this, value);
    }

    template <typename Type>
    inline vec2<Type> &vec2<Type>::operator*=(const Type &value)
    {
        *this = mul(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::operator/(const Type &value) const
    {
        return div(*this, value);
    }

    template <typename Type>
    inline vec2<Type> &vec2<Type>::operator/=(const Type &value)
    {
        *this = div(*this, value);

        return *this;
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::yx() const
    {
        return vec2<Type>(y, x);
    }

    template <typename Type>
    inline float vec2<Type>::get_length() const
    {
        return magn(*this);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::sub(const vec2 &vec, const Type &value)
    {
        return vec2<Type>(
                vec.x - value,
                value.y - value);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::sub(const vec2 &vec1, const vec2 &vec2)
    {
        return vec2<Type>(
                vec1.x - vec2.x,
                vec1.y - vec2.y);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::add(const vec2 &vec, const Type &value)
    {
        return vec2<Type>(
                vec.x + value,
                vec.y + value);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::add(const vec2 &vec1, const vec2 &vec2)
    {
        return vec2<Type>(
                vec1.x + vec2.x,
                vec1.y + vec2.y);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::mul(const vec2 &vec, const Type &value)
    {
        return vec2<Type>(
                vec.x * value,
                vec.y * value);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::div(const vec2 &vec, const Type &value)
    {
        return vec2<Type>(
                vec.x / value,
                vec.y / value);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::scale(const vec2 &v, const Type &scalar)
    {
        return vec2<Type>::mul(v, scalar);
    }

    template <typename Type>
    inline float vec2<Type>::magn(const vec2 &vec)
    {
        return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::norm(const vec2 &vec)
    {
        float length = magn(vec);

        return vec2<Type>(
                vec.x / length,
                vec.y / length);
    }

    template <typename Type>
    inline float vec2<Type>::dot(const vec2 &vec1, const vec2 &vec2)
    {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    template <typename Type>
    inline vec2<Type> vec2<Type>::inv(const vec2 &vec)
    {
        return scale(*this, static_cast<Type>(-1));
    }
} // namespace deep

#endif
