#ifndef DEEP_LIB_MATH_HPP
#define DEEP_LIB_MATH_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

#ifndef DEEP_MIN
#define DEEP_MIN(first, second) (first < second ? first : second)
#endif

#ifndef DEEP_MAX
#define DEEP_MAX(first, second) (first > second ? first : second)
#endif

namespace deep
{
    class DEEP_LIB_API math
    {
      public:
        static constexpr long double PI = 3.14159265358979323846;

        static constexpr int8 min(int8 first, int8 second);
        static constexpr int16 min(int16 first, int16 second);
        static constexpr int32 min(int32 first, int32 second);
        static constexpr int64 min(int64 first, int64 second);
        static constexpr uint8 min(uint8 first, uint8 second);
        static constexpr uint16 min(uint16 first, uint16 second);
        static constexpr uint32 min(uint32 first, uint32 second);
        static constexpr uint64 min(uint64 first, uint64 second);

        static constexpr int8 max(int8 first, int8 second);
        static constexpr int16 max(int16 first, int16 second);
        static constexpr int32 max(int32 first, int32 second);
        static constexpr int64 max(int64 first, int64 second);
        static constexpr uint8 max(uint8 first, uint8 second);
        static constexpr uint16 max(uint16 first, uint16 second);
        static constexpr uint32 max(uint32 first, uint32 second);
        static constexpr uint64 max(uint64 first, uint64 second);

        template <typename Type>
        static constexpr Type deg_to_rad(Type degrees) noexcept;

        static constexpr uint8 abs(int8 value) noexcept;
        static constexpr uint16 abs(int16 value) noexcept;
        static constexpr uint32 abs(int32 value) noexcept;
        static constexpr uint64 abs(int64 value) noexcept;
        static constexpr float abs(float value) noexcept;
        static constexpr double abs(double value) noexcept;
        static constexpr long double abs(long double value) noexcept;
    };

    inline constexpr int8 math::min(int8 first, int8 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr int16 math::min(int16 first, int16 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr int32 math::min(int32 first, int32 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr int64 math::min(int64 first, int64 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr uint8 math::min(uint8 first, uint8 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr uint16 math::min(uint16 first, uint16 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr uint32 math::min(uint32 first, uint32 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr uint64 math::min(uint64 first, uint64 second)
    {
        return DEEP_MIN(first, second);
    }

    inline constexpr int8 math::max(int8 first, int8 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr int16 math::max(int16 first, int16 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr int32 math::max(int32 first, int32 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr int64 math::max(int64 first, int64 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr uint8 math::max(uint8 first, uint8 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr uint16 math::max(uint16 first, uint16 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr uint32 math::max(uint32 first, uint32 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr uint64 math::max(uint64 first, uint64 second)
    {
        return DEEP_MAX(first, second);
    }

    inline constexpr uint8 math::abs(int8 value) noexcept
    {
        if (value >= 0)
        {
            return DEEP_U8(value);
        }

        return DEEP_U8(0) - DEEP_U8(value);
    }

    inline constexpr uint16 math::abs(int16 value) noexcept
    {
        if (value >= 0)
        {
            return DEEP_U16(value);
        }

        return DEEP_U16(0) - DEEP_U16(value);
    }

    inline constexpr uint32 math::abs(int32 value) noexcept
    {
        if (value >= 0)
        {
            return DEEP_U32(value);
        }

        return DEEP_U32(0) - DEEP_U32(value);
    }

    inline constexpr uint64 math::abs(int64 value) noexcept
    {
        if (value >= 0)
        {
            return DEEP_U64(value);
        }

        return DEEP_U64(0) - DEEP_U64(value);
    }

    inline constexpr float math::abs(float value) noexcept
    {
        return value >= 0.0f ? value : -value;
    }

    inline constexpr double math::abs(double value) noexcept
    {
        return value >= 0.0 ? value : -value;
    }

    inline constexpr long double math::abs(long double value) noexcept
    {
        return value >= 0.0 ? value : -value;
    }
    template <typename Type>
    inline constexpr Type math::deg_to_rad(Type degrees) noexcept
    {
        return static_cast<Type>(degrees * (PI / 180.0));
    }
} // namespace deep

#endif
