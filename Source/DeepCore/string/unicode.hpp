#ifndef DEEP_CORE_UNICODE_HPP
#define DEEP_CORE_UNICODE_HPP

#include "deep_core_export.h"
#include "../types.hpp"

namespace deep
{
    class DEEP_CORE_API core_unicode
    {
      public:
        static usize calc_bytes_size(const wchar *str);
        static usize calc_length(const wchar *str);
    };
} // namespace deep

#endif
