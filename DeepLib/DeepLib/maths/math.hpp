#ifndef DEEP_LIB_PNG_HPP
#define DEEP_LIB_PNG_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_LIB_API math
    {
      public:
        static constexpr uint8 min(uint8 first, uint8 second);
        static constexpr uint16 min(uint16 first, uint16 second);
        static constexpr uint32 min(uint32 first, uint32 second);
        static constexpr uint64 min(uint64 first, uint64 second);

        static constexpr uint8 max(uint8 first, uint8 second);
        static constexpr uint16 max(uint16 first, uint16 second);
        static constexpr uint32 max(uint32 first, uint32 second);
        static constexpr uint64 max(uint64 first, uint64 second);
    };

    inline constexpr uint8 math::min(uint8 first, uint8 second)
    {
        return first < second ? first : second;
    }

    inline constexpr uint16 math::min(uint16 first, uint16 second)
    {
        return first < second ? first : second;
    }

    inline constexpr uint32 math::min(uint32 first, uint32 second)
    {
        return first < second ? first : second;
    }

    inline constexpr uint64 math::min(uint64 first, uint64 second)
    {
        return first < second ? first : second;
    }

    inline constexpr uint8 math::max(uint8 first, uint8 second)
    {
        return first > second ? first : second;
    }

    inline constexpr uint16 math::max(uint16 first, uint16 second)
    {
        return first > second ? first : second;
    }

    inline constexpr uint32 math::max(uint32 first, uint32 second)
    {
        return first > second ? first : second;
    }

    inline constexpr uint64 math::max(uint64 first, uint64 second)
    {
        return first > second ? first : second;
    }
} // namespace deep

#endif
