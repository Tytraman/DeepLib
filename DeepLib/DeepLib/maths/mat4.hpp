#ifndef DEEP_LIB_MAT4_HPP
#define DEEP_LIB_MAT4_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/maths/math.hpp"
#include "DeepLib/maths/vec3.hpp"

#include <cmath>
#include <cstring>

namespace deep
{
    /**
     * @brief Matrice 4x4 en 'Row-Major'.
     * @tparam Type
     */
    template <typename Type>
    struct mat4x4
    {
        static_assert(is_primitive<Type>, "Type must be primitive");

        static constexpr Rows    = 4;
        static constexpr Columns = 4;

        Type data[Rows][Columns];

        mat4x4(
                Type m00 = 1, Type m01 = 0, Type m02 = 0, Type m03 = 0,
                Type m10 = 0, Type m11 = 1, Type m12 = 0, Type m13 = 0,
                Type m20 = 0, Type m21 = 0, Type m22 = 1, Type m23 = 0,
                Type m30 = 0, Type m31 = 0, Type m32 = 0, Type m33 = 1);

        mat4x4<Type> operator*(const mat4x4<Type> &mat) const;
        mat4x4<Type> &operator*=(const mat4x4<Type> &mat);
        Type &operator[](usize index);
        const Type &operator[](usize index) const;
        bool operator==(const mat4x4<Type> &other) const;

        const Type *get() const;

        static mat4x4<Type> mul(const mat4x4<Type> &matrix);
        static mat4x4<Type> mul(const mat4x4<Type> &mat1, const mat4x4<Type> &mat2);

        static mat4x4<Type> row_translate(const mat4x4<Type> &mat, const vec3<Type> &vec);
        static mat4x4<Type> column_translate(const mat4x4<Type> &mat, const vec3<Type> &vec);
        static mat4x4<Type> scale(const mat4x4<Type> &mat, const vec3<Type> &vec);
        static mat4x4<Type> row_rotate_x(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> column_rotate_x(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> row_rotate_y(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> column_rotate_y(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> row_rotate_z(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> column_rotate_z(const mat4x4<Type> &mat, Type degrees);
        static mat4x4<Type> perspective(Type fov, Type aspect_ratio, Type z_near, Type z_far);
        static mat4x4<Type> d3d_perspective_lh(Type width, Type height, Type z_near, Type z_far);
        static mat4x4<Type> transpose(const mat4x4<Type> &mat);
    };

    template <typename Type>
    inline mat4x4<Type>::mat4x4(Type m00, Type m01, Type m02, Type m03,
                                Type m10, Type m11, Type m12, Type m13,
                                Type m20, Type m21, Type m22, Type m23,
                                Type m30, Type m31, Type m32, Type m33)
    {
        data[0][0] = m00;
        data[0][1] = m01;
        data[0][2] = m02;
        data[0][3] = m03;

        data[1][0] = m10;
        data[1][1] = m11;
        data[1][2] = m12;
        data[1][3] = m13;

        data[2][0] = m20;
        data[2][1] = m21;
        data[2][2] = m22;
        data[2][3] = m23;

        data[3][0] = m30;
        data[3][1] = m31;
        data[3][2] = m32;
        data[3][3] = m33;
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
    inline mat4x4<Type> mat4x4<Type>::row_translate(const mat4x4<Type> &mat, const vec3<Type> &vec)
    {
        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           vec.x,

                           static_cast<Type>(0),
                           static_cast<Type>(1),
                           static_cast<Type>(0),
                           vec.y,

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1),
                           vec.z,

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::column_translate(const mat4x4<Type> &mat, const vec3<Type> &vec)
    {
        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0),
                           vec.x, vec.y, vec.z, static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::scale(const mat4x4<Type> &mat, const vec3<Type> &vec)
    {
        return mul(mat,
                   mat4x4<Type>(
                           vec.x,
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           vec.y,
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           vec.z,
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::row_rotate_x(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           std::cos(rad),
                           -std::sin(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           std::sin(rad),
                           std::cos(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::column_rotate_x(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           std::cos(rad),
                           std::sin(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           -std::sin(rad),
                           std::cos(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::row_rotate_y(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           std::cos(rad),
                           static_cast<Type>(0),
                           std::sin(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(1),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           -std::sin(rad),
                           static_cast<Type>(0),
                           std::cos(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::column_rotate_y(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           std::cos(rad),
                           static_cast<Type>(0),
                           -std::sin(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(1),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           std::sin(rad),
                           static_cast<Type>(0),
                           std::cos(rad),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::row_rotate_z(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           std::cos(rad),
                           -std::sin(rad),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           std::sin(rad),
                           std::cos(rad),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
    }

    template <typename Type>
    inline mat4x4<Type> mat4x4<Type>::column_rotate_z(const mat4x4<Type> &mat, Type degrees)
    {
        Type rad = math::deg_to_rad(degrees);

        return mul(mat,
                   mat4x4<Type>(
                           std::cos(rad),
                           std::sin(rad),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           -std::sin(rad),
                           std::cos(rad),
                           static_cast<Type>(0),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1),
                           static_cast<Type>(0),

                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(0),
                           static_cast<Type>(1)));
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
    inline mat4x4<Type> mat4x4<Type>::d3d_perspective_lh(Type width, Type height, Type z_near, Type z_far)
    {
        return mat4x4<Type>(
                static_cast<Type>(2) * z_near / width, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(2) * z_near / height, static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(0), z_far / (z_far - z_near), static_cast<Type>(1),
                static_cast<Type>(0), static_cast<Type>(0), z_near * z_far / (z_near - z_far), static_cast<Type>(0));
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
