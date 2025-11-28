#include "math.hpp"

namespace deep
{
    uint8 math::abs(int8 value)
    {
        if (value >= 0)
        {
            return DEEP_U8(value);
        }

        return DEEP_U8(0) - DEEP_U8(value);
    }

    uint16 math::abs(int16 value)
    {
        if (value >= 0)
        {
            return DEEP_U16(value);
        }

        return DEEP_U16(0) - DEEP_U16(value);
    }

    uint32 math::abs(int32 value)
    {
        if (value >= 0)
        {
            return DEEP_U32(value);
        }

        return DEEP_U32(0) - DEEP_U32(value);
    }

    uint64 math::abs(int64 value)
    {
        if (value >= 0)
        {
            return DEEP_U64(value);
        }

        return DEEP_U64(0) - DEEP_U64(value);
    }
} // namespace deep
