#ifndef DEEP_CORE_UTF8_HPP
#define DEEP_CORE_UTF8_HPP

#include "deep_core_export.h"
#include "../types.hpp"

namespace deep
{
    class DEEP_CORE_API core_utf8
    {
      public:
        static usize calc_bytes_size(const char *str);
        static usize calc_length(const char *str);
    };
} // namespace deep

#endif
