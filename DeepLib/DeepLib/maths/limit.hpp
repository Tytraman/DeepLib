#ifndef DEEP_LIB_LIMIT_HPP
#define DEEP_LIB_LIMIT_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_LIB_API limit
    {
      public:
        static constexpr int8 MIN_INT8   = DEEP_I8(DEEP_U8(1) << 7);
        static constexpr int8 MAX_INT8   = DEEP_I8(~MIN_INT8);
        static constexpr int16 MIN_INT16 = DEEP_I16(DEEP_U16(1) << 15);
        static constexpr int16 MAX_INT16 = DEEP_I16(~MIN_INT16);
        static constexpr int32 MIN_INT32 = DEEP_I32(DEEP_U32(1) << 31);
        static constexpr int32 MAX_INT32 = DEEP_I32(~MIN_INT32);
        static constexpr int64 MIN_INT64 = DEEP_I64(DEEP_U64(1) << 63);
        static constexpr int64 MAX_INT64 = DEEP_I64(~MIN_INT64);

        static constexpr uint8 MIN_UINT8   = DEEP_U8(0);
        static constexpr uint8 MAX_UINT8   = DEEP_U8(~MIN_UINT8);
        static constexpr uint16 MIN_UINT16 = DEEP_U16(0);
        static constexpr uint16 MAX_UINT16 = DEEP_U16(~MIN_UINT16);
        static constexpr uint32 MIN_UINT32 = DEEP_U32(0);
        static constexpr uint32 MAX_UINT32 = DEEP_U32(~MIN_UINT32);
        static constexpr uint64 MIN_UINT64 = DEEP_U64(0);
        static constexpr uint64 MAX_UINT64 = DEEP_U64(~MIN_UINT64);
    };
} // namespace deep

#endif
