#ifndef DEEP_LIB_MAT4_HPP
#define DEEP_LIB_MAT4_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/maths/math.hpp"
#include "DeepLib/maths/vec3.hpp"
#include "DeepLib/maths/vec4.hpp"
#include "DeepLib/string/string.hpp"

#include <cmath>
#include <cstring>

namespace deep
{
    /**
     * @brief Matrice 4x4 en 'Row-Major' et 'Vecteur Colonne'.
     * @tparam Type
     */
    template <typename Type>
    struct alignas(16) mat4x4
    {
        static_assert(is_primitive<Type>, "Type must be primitive");

        static constexpr uint8 RowCount    = 4;
        static constexpr uint8 ColumnCount = 4;

        /*
         *   | x0, y0, z0, w0 |
         *   | x1, y1, z1, w1 |
         *   | x2, y2, z2, w2 |
         *   | x3, y3, z3, w3 |
         */
        vec4<Type> rows[RowCount];

        constexpr mat4x4(
                Type m00 = 1, Type m01 = 0, Type m02 = 0, Type m03 = 0,
                Type m10 = 0, Type m11 = 1, Type m12 = 0, Type m13 = 0,
                Type m20 = 0, Type m21 = 0, Type m22 = 1, Type m23 = 0,
                Type m30 = 0, Type m31 = 0, Type m32 = 0, Type m33 = 1) noexcept;

        constexpr mat4x4<Type> operator*(const mat4x4<Type> &mat) const noexcept;
        constexpr mat4x4<Type> &operator*=(const mat4x4<Type> &mat) noexcept;

        constexpr const vec4<Type> &operator[](uint8 index) const noexcept;
        constexpr vec4<Type> &operator[](usize index) noexcept;

        constexpr bool operator==(const mat4x4<Type> &other) const noexcept;

        constexpr const Type *get() const noexcept;

        string to_string(const ref<ctx> &context) const noexcept;

        constexpr static mat4x4<Type> mul(const mat4x4<Type> &m, const mat4x4<Type> &n) noexcept;

        constexpr static mat4x4<Type> translate(const mat4x4<Type> &mat, const vec3<Type> &vec) noexcept;
        constexpr static mat4x4<Type> scale(const mat4x4<Type> &mat, const vec3<Type> &vec) noexcept;
        /*constexpr*/ static mat4x4<Type> rotate_x(const mat4x4<Type> &mat, Type degrees) noexcept;
        /*constexpr*/ static mat4x4<Type> rotate_y(const mat4x4<Type> &mat, Type degrees) noexcept;
        /*constexpr*/ static mat4x4<Type> rotate_z(const mat4x4<Type> &mat, Type degrees) noexcept;
        constexpr static mat4x4<Type> d3d_perspective_lh(Type width, Type height, Type z_near, Type z_far) noexcept;
        constexpr static mat4x4<Type> d3d_perspective_fov_lh(Type fov, Type aspect_ratio, Type z_near, Type z_far) noexcept;
        constexpr static mat4x4<Type> d3d_look_at_lh(const fvec3 &from, const fvec3 &to, const fvec3 &up) noexcept;
        constexpr static mat4x4<Type> transpose(const mat4x4<Type> &m) noexcept;
    };

    template <typename Type>
    inline constexpr mat4x4<Type>::mat4x4(Type m00, Type m01, Type m02, Type m03,
                                          Type m10, Type m11, Type m12, Type m13,
                                          Type m20, Type m21, Type m22, Type m23,
                                          Type m30, Type m31, Type m32, Type m33) noexcept
    {
        rows[0] = vec4<Type>(m00, m01, m02, m03);
        rows[1] = vec4<Type>(m10, m11, m12, m13);
        rows[2] = vec4<Type>(m20, m21, m22, m23);
        rows[3] = vec4<Type>(m30, m31, m32, m33);
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::operator*(const mat4x4<Type> &mat) const noexcept
    {
        return mul(*this, mat);
    }

    template <typename Type>
    inline constexpr mat4x4<Type> &mat4x4<Type>::operator*=(const mat4x4<Type> &mat) noexcept
    {
        *this = mul(*this, mat);

        return *this;
    }

    template <typename Type>
    inline constexpr const vec4<Type> &mat4x4<Type>::operator[](uint8 index) const noexcept
    {
        return rows[index];
    }

    template <typename Type>
    inline constexpr vec4<Type> &mat4x4<Type>::operator[](usize index) noexcept
    {
        return rows[index];
    }

    template <typename Type>
    inline constexpr bool mat4x4<Type>::operator==(const mat4x4<Type> &other) const noexcept
    {
        if constexpr (is_floating_point<Type>)
        {
            constexpr Type epsilon = static_cast<Type>(0.000001);

            for (uint8 row = 0; row < RowCount; ++row)
            {
                for (uint8 column = 0; column < ColumnCount; ++column)
                {
                    if (math::abs(rows[row][column] - other.rows[row][column]) > epsilon)
                    {
                        return false;
                    }
                }
            }

            return true;
        }
        else
        {
            return std::memcmp(rows, other.rows, sizeof(rows)) == 0;
        }
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::mul(const mat4x4 &m, const mat4x4 &n) noexcept
    {
        return mat4x4<Type>(
                // 1ère ligne.
                (m[0][0] * n[0][0] +
                 m[0][1] * n[1][0] +
                 m[0][2] * n[2][0] +
                 m[0][3] * n[3][0]),

                (m[0][0] * n[0][1] +
                 m[0][1] * n[1][1] +
                 m[0][2] * n[2][1] +
                 m[0][3] * n[3][1]),

                (m[0][0] * n[0][2] +
                 m[0][1] * n[1][2] +
                 m[0][2] * n[2][2] +
                 m[0][3] * n[3][2]),

                (m[0][0] * n[0][3] +
                 m[0][1] * n[1][3] +
                 m[0][2] * n[2][3] +
                 m[0][3] * n[3][3]),

                // 2ème ligne
                (m[1][0] * n[0][0] +
                 m[1][1] * n[1][0] +
                 m[1][2] * n[2][0] +
                 m[1][3] * n[3][0]),

                (m[1][0] * n[0][1] +
                 m[1][1] * n[1][1] +
                 m[1][2] * n[2][1] +
                 m[1][3] * n[3][1]),

                (m[1][0] * n[0][2] +
                 m[1][1] * n[1][2] +
                 m[1][2] * n[2][2] +
                 m[1][3] * n[3][2]),

                (m[1][0] * n[0][3] +
                 m[1][1] * n[1][3] +
                 m[1][2] * n[2][3] +
                 m[1][3] * n[3][3]),

                // 3ème ligne
                (m[2][0] * n[0][0] +
                 m[2][1] * n[1][0] +
                 m[2][2] * n[2][0] +
                 m[2][3] * n[3][0]),

                (m[2][0] * n[0][1] +
                 m[2][1] * n[1][1] +
                 m[2][2] * n[2][1] +
                 m[2][3] * n[3][1]),

                (m[2][0] * n[0][2] +
                 m[2][1] * n[1][2] +
                 m[2][2] * n[2][2] +
                 m[2][3] * n[3][2]),

                (m[2][0] * n[0][3] +
                 m[2][1] * n[1][3] +
                 m[2][2] * n[2][3] +
                 m[2][3] * n[3][3]),

                // 4ème ligne
                (m[3][0] * n[0][0] +
                 m[3][1] * n[1][0] +
                 m[3][2] * n[2][0] +
                 m[3][3] * n[3][0]),

                (m[3][0] * n[0][1] +
                 m[3][1] * n[1][1] +
                 m[3][2] * n[2][1] +
                 m[3][3] * n[3][1]),

                (m[3][0] * n[0][2] +
                 m[3][1] * n[1][2] +
                 m[3][2] * n[2][2] +
                 m[3][3] * n[3][2]),

                (m[3][0] * n[0][3] +
                 m[3][1] * n[1][3] +
                 m[3][2] * n[2][3] +
                 m[3][3] * n[3][3]));
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::translate(const mat4x4<Type> &mat, const vec3<Type> &vec) noexcept
    {
        return mul(mat,
                   mat4x4<Type>(
                           static_cast<Type>(1), static_cast<Type>(0), static_cast<Type>(0), vec.x,
                           static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0), vec.y,
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), vec.z,
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::scale(const mat4x4<Type> &mat, const vec3<Type> &vec) noexcept
    {
        return mul(mat,
                   mat4x4<Type>(
                           vec.x, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), vec.y, static_cast<Type>(0), static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), vec.z, static_cast<Type>(0),
                           static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1)));
    }

    template <typename Type>
    inline /*constexpr*/ mat4x4<Type> mat4x4<Type>::rotate_x(const mat4x4<Type> &mat, Type degrees) noexcept
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
    inline /*constexpr*/ mat4x4<Type> mat4x4<Type>::rotate_y(const mat4x4<Type> &mat, Type degrees) noexcept
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
    inline /*constexpr*/ mat4x4<Type> mat4x4<Type>::rotate_z(const mat4x4<Type> &mat, Type degrees) noexcept
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
    inline constexpr mat4x4<Type> mat4x4<Type>::d3d_perspective_lh(Type width, Type height, Type z_near, Type z_far) noexcept
    {
        return mat4x4<Type>(
                static_cast<Type>(2) * z_near / width, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(2) * z_near / height, static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(0), z_far / (z_far - z_near), z_near * z_far / (z_near - z_far),
                static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0));
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::d3d_perspective_fov_lh(Type fov, Type aspect_ratio, Type z_near, Type z_far) noexcept
    {
        fov = math::deg_to_rad(fov);

        Type y_scale = static_cast<Type>(1) / std::tan(fov / static_cast<Type>(2));
        Type x_scale = y_scale / aspect_ratio;

        return mat4x4<Type>(
                x_scale, static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), y_scale, static_cast<Type>(0), static_cast<Type>(0),
                static_cast<Type>(0), static_cast<Type>(0), z_far / (z_far - z_near), -z_near * z_far / (z_far - z_near),
                static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1), static_cast<Type>(0));
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::d3d_look_at_lh(const fvec3 &from, const fvec3 &to, const fvec3 &up) noexcept
    {
        fvec3 forward_axis = fvec3::norm(to - from);
        fvec3 right_axis   = fvec3::norm(fvec3::cross(up, forward_axis));
        fvec3 up_axis      = fvec3::cross(forward_axis, right_axis);

        return mat4x4<Type>(
                right_axis.x, right_axis.y, right_axis.z, -fvec3::dot(right_axis, from),
                up_axis.x, up_axis.y, up_axis.z, -fvec3::dot(up_axis, from),
                forward_axis.x, forward_axis.y, forward_axis.z, -fvec3::dot(forward_axis, from),
                static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(1));
    }

    template <typename Type>
    inline constexpr mat4x4<Type> mat4x4<Type>::transpose(const mat4x4<Type> &m) noexcept
    {
        return mat4x4<Type>(
                m[0][0], m[1][0], m[2][0], m[3][0],
                m[0][1], m[1][1], m[2][1], m[3][1],
                m[0][2], m[1][2], m[2][2], m[3][2],
                m[0][3], m[1][3], m[2][3], m[3][3]);
    }

    template <typename Type>
    inline constexpr const Type *mat4x4<Type>::get() const noexcept
    {
        return &(rows[0].x);
    }

    template <typename Type>
    string mat4x4<Type>::to_string(const ref<ctx> &context) const noexcept
    {
        string s = string(context);

        uint8 row, col;

        for (row = 0; row < RowCount; ++row)
        {
            s.append("[ ");

            for (col = 0; col < ColumnCount - 1; ++col)
            {
                string value = string::from(context, rows[row][col], 3);

                s.append(*value);
                s.append(", ");
            }

            string value = string::from(context, rows[row][col], 3);

            s.append(*value);

            s.append(" ]\r\n");
        }

        return s;
    }
} // namespace deep

#endif
