#ifndef DEEP_LIB_MAT4_HPP
#define DEEP_LIB_MAT4_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/maths/math.hpp"
#include "DeepLib/maths/vec3.hpp"

#include <cmath>
#include <cstring>

namespace deep
{
    template <typename Type>
    struct mat4x4
    {
        static_assert(is_primitive<Type>, "Type must be primitive");

        static constexpr usize x1 = 0;
        static constexpr usize y1 = 1;
        static constexpr usize z1 = 2;
        static constexpr usize w1 = 3;
        static constexpr usize x2 = 4;
        static constexpr usize y2 = 5;
        static constexpr usize z2 = 6;
        static constexpr usize w2 = 7;
        static constexpr usize x3 = 8;
        static constexpr usize y3 = 9;
        static constexpr usize z3 = 10;
        static constexpr usize w3 = 11;
        static constexpr usize x4 = 12;
        static constexpr usize y4 = 13;
        static constexpr usize z4 = 14;
        static constexpr usize w4 = 15;

        Type data[4 * 4];

        mat4x4(
                Type x1 = 1, Type y1 = 0, Type z1 = 0, Type w1 = 0,
                Type x2 = 0, Type y2 = 1, Type z2 = 0, Type w2 = 0,
                Type x3 = 0, Type y3 = 0, Type z3 = 1, Type w3 = 0,
                Type x4 = 0, Type y4 = 0, Type z4 = 0, Type w4 = 1);

        mat4x4<Type> operator*(const mat4x4<Type> &mat) const;
        mat4x4<Type> &operator*=(const mat4x4<Type> &mat);
        Type &operator[](usize index);
        const Type &operator[](usize index) const;
        bool operator==(const mat4x4<Type> &other) const;

        const Type *get() const;

        static mat4x4<Type> mul(const mat4x4<Type> &mat1, const mat4x4<Type> &mat2);

        static mat4x4<Type> translate(const mat4x4<Type> &mat, const vec3<Type> &vec);
        static mat4x4<Type> scale(const mat4x4<Type> &mat, const vec3<Type> &vec);
        static mat4x4<Type> rotate_x(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> rotate_y(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> rotate_z(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> perspective(Type fov, Type aspect_ratio, Type z_near, Type z_far);
        static mat4x4<Type> transpose(const mat4x4<Type> &mat);
    };

    template <typename Type>
    inline mat4x4<Type>::mat4x4(Type _x1, Type _y1, Type _z1, Type _w1,
                                Type _x2, Type _y2, Type _z2, Type _w2,
                                Type _x3, Type _y3, Type _z3, Type _w3,
                                Type _x4, Type _y4, Type _z4, Type _w4)
    {
        data[x1] = _x1;
        data[y1] = _y1;
        data[z1] = _z1;
        data[w1] = _w1;

        data[x2] = _x2;
        data[y2] = _y2;
        data[z2] = _z2;
        data[w2] = _w2;

        data[x3] = _x3;
        data[y3] = _y3;
        data[z3] = _z3;
        data[w3] = _w3;

        data[x4] = _x4;
        data[y4] = _y4;
        data[z4] = _z4;
        data[w4] = _w4;
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::operator*(const mat4x4<Type> &mat) const
    {
        return mul(*this, mat);
    }

    template <typename Type>
    inline mat4x4<Type> &mat4x4<Type>::operator*=(const mat4x4<Type> &mat)
    {
        *this = mul(*this, mat);

        return *this;
    }

    template <typename Type>
    inline Type &mat4x4<Type>::operator[](usize index)
    {
        return data[index];
    }

    template <typename Type>
    inline const Type &mat4x4<Type>::operator[](usize index) const
    {
        return data[index];
    }

    template <typename Type>
    inline bool mat4x4<Type>::operator==(const mat4x4<Type> &other) const
    {
        if constexpr (is_floating_point<Type>)
        {
            constexpr Type epsilon = 0.000001;

            for (usize index = 0; index < 4 * 4; ++index)
            {
                if (math::abs(data[index] - other.data[index]) > epsilon)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            return std::memcmp(data, other.data, sizeof(data)) == 0;
        }
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::mul(const mat4x4 &mat1, const mat4x4 &mat2)
    {
        return mat4x4<Type>(
                (mat1[x1] * mat2[x1] +
                 mat1[y1] * mat2[x2] +
                 mat1[z1] * mat2[x3] +
                 mat1[w1] * mat2[x4]),

                (mat1[x1] * mat2[y1] +
                 mat1[y1] * mat2[y2] +
                 mat1[z1] * mat2[y3] +
                 mat1[w1] * mat2[y4]),

                (mat1[x1] * mat2[z1] +
                 mat1[y1] * mat2[z2] +
                 mat1[z1] * mat2[z3] +
                 mat1[w1] * mat2[z4]),

                (mat1[x1] * mat2[w1] +
                 mat1[y1] * mat2[w2] +
                 mat1[z1] * mat2[w3] +
                 mat1[w1] * mat2[w4]),

                (mat1[x2] * mat2[x1] +
                 mat1[y2] * mat2[x2] +
                 mat1[z2] * mat2[x3] +
                 mat1[w2] * mat2[x4]),

                (mat1[x2] * mat2[y1] +
                 mat1[y2] * mat2[y2] +
                 mat1[z2] * mat2[y3] +
                 mat1[w2] * mat2[y4]),

                (mat1[x2] * mat2[z1] +
                 mat1[y2] * mat2[z2] +
                 mat1[z2] * mat2[z3] +
                 mat1[w2] * mat2[z4]),

                (mat1[x2] * mat2[w1] +
                 mat1[y2] * mat2[w2] +
                 mat1[z2] * mat2[w3] +
                 mat1[w2] * mat2[w4]),

                (mat1[x3] * mat2[x1] +
                 mat1[y3] * mat2[x2] +
                 mat1[z3] * mat2[x3] +
                 mat1[w3] * mat2[x4]),

                (mat1[x3] * mat2[y1] +
                 mat1[y3] * mat2[y2] +
                 mat1[z3] * mat2[y3] +
                 mat1[w3] * mat2[y4]),

                (mat1[x3] * mat2[z1] +
                 mat1[y3] * mat2[z2] +
                 mat1[z3] * mat2[z3] +
                 mat1[w3] * mat2[z4]),

                (mat1[x3] * mat2[w1] +
                 mat1[y3] * mat2[w2] +
                 mat1[z3] * mat2[w3] +
                 mat1[w3] * mat2[w4]),

                (mat1[x4] * mat2[x1] +
                 mat1[y4] * mat2[x2] +
                 mat1[z4] * mat2[x3] +
                 mat1[w4] * mat2[x4]),

                (mat1[x4] * mat2[y1] +
                 mat1[y4] * mat2[y2] +
                 mat1[z4] * mat2[y3] +
                 mat1[w4] * mat2[y4]),

                (mat1[x4] * mat2[z1] +
                 mat1[y4] * mat2[z2] +
                 mat1[z4] * mat2[z3] +
                 mat1[w4] * mat2[z4]),

                (mat1[x4] * mat2[w1] +
                 mat1[y4] * mat2[w2] +
                 mat1[z4] * mat2[w3] +
                 mat1[w4] * mat2[w4]));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::translate(const mat4x4<Type> &mat, const vec3<Type> &vec)
    {
        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0), vec.x,
                           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), vec.y,
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), vec.z,
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::scale(const mat4x4<Type> &mat, const vec3<Type> &vec)
    {
        return mul(mat,
                   mat4x4<Type>(
                           vec.x, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), vec.y, static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), vec.z, static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::rotate_x(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), std::cos(rad), -std::sin(rad), static_cast<Type>(0),
                           static_cast<Type>(0), std::sin(rad), std::cos(rad), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::rotate_y(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           std::cos(rad), static_cast<Type>(0), std::sin(rad), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0),
                           -std::sin(rad), static_cast<Type>(0), std::cos(rad), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::rotate_z(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           std::cos(rad), -std::sin(rad), static_cast<Type>(0), static_cast<Type>(0),
                           std::sin(rad), std::cos(rad), static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::perspective(Type fov, Type aspect_ratio, Type z_near, Type z_far)
    {
        Type tan_half_fov = std::tan(fov / 2.0);
        Type zr           = z_far - z_near;

        return mat4x4<Type>(
                static_cast<Type>(1) / (aspect_ratio * tan_half_fov), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(1) / tan_half_fov, static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(0), -(z_far + z_near) / zr, -(static_cast<Type>(2) * z_far * z_near) / zr,
                static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(-1), static_cast<Type>(0));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::transpose(const mat4x4<Type> &mat)
    {
        return mat4x4<Type>(
                mat[x1], mat[x2], mat[x3], mat[x4],
                mat[y1], mat[y2], mat[y3], mat[y4],
                mat[z1], mat[z2], mat[z3], mat[z4],
                mat[w1], mat[w2], mat[w3], mat[w4]);
    }

    template <typename Type>
    inline const Type *mat4x4<Type>::get() const
    {
        return data;
    }
} // namespace deep

#endif
