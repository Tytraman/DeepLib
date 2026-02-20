#ifndef DEEP_LIB_STRING_UTILS_HPP
#define DEEP_LIB_STRING_UTILS_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_LIB_API string_utils
    {
      public:
        static uint64 hash(const char *utf8_str);
    };
} // namespace deep

#endif
