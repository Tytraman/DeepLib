#ifndef DEEP_LIB_VEC_HPP
#define DEEP_LIB_VEC_HPP

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

#include "DeepLib/maths/vec2.hpp"
#include "DeepLib/maths/vec3.hpp"
#include "DeepLib/maths/vec4.hpp"

#if defined(_MSC_VER)

#define DEEP_FVEC2                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec2<float>         \
                    __pragma(warning(pop))

#define DEEP_IVEC2                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec2<deep::int32>   \
                    __pragma(warning(pop))

#define DEEP_UVEC2                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec2<deep::uint32>  \
                    __pragma(warning(pop))

#define DEEP_FVEC3                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec3<float>         \
                    __pragma(warning(pop))

#define DEEP_IVEC3                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec3<deep::int32>   \
                    __pragma(warning(pop))

#define DEEP_UVEC3                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec3<deep::uint32>  \
                    __pragma(warning(pop))

#define DEEP_FVEC4                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec4<float>         \
                    __pragma(warning(pop))

#define DEEP_IVEC4                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec4<deep::int32>   \
                    __pragma(warning(pop))

#define DEEP_UVEC4                            \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::vec4<deep::uint32>  \
                    __pragma(warning(pop))

#else
#define DEEP_FVEC2 deep::vec2<float>
#define DEEP_IVEC2 deep::vec2<deep::int32>
#define DEEP_UVEC2 deep::vec2<deep::uint32>
#define DEEP_FVEC3 deep::vec3<float>
#define DEEP_IVEC3 deep::vec3<deep::int32>
#define DEEP_UVEC3 deep::vec3<deep::uint32>
#define DEEP_FVEC4 deep::vec4<float>
#define DEEP_IVEC4 deep::vec4<deep::int32>
#define DEEP_UVEC4 deep::vec4<deep::uint32>
#endif

namespace deep
{
    using fvec2 = DEEP_FVEC2;
    using ivec2 = DEEP_IVEC2;
    using uvec2 = DEEP_UVEC2;

    using fvec3 = DEEP_FVEC3;
    using ivec3 = DEEP_IVEC3;
    using uvec3 = DEEP_UVEC3;

    using fvec4 = DEEP_FVEC4;
    using ivec4 = DEEP_IVEC4;
    using uvec4 = DEEP_UVEC4;
} // namespace deep

#endif
