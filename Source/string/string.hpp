#ifndef DEEP_LIB_STRING_HPP
#define DEEP_LIB_STRING_HPP

#include "deep_lib_export.h"
#include "string_base.hpp"
#include "DeepCore/string/utf8.hpp"

namespace deep
{
    class string : public string_base<string, char>
    {
      public:
        using string_base<string, char>::string_base;

        static constexpr string_encoding encoding = string_encoding::UTF8;

        static usize calc_bytes_size_impl(const char *str);
        static usize calc_length_impl(const char *str);
    };

    inline usize deep::string::calc_bytes_size_impl(const char *str)
    {
        return core_utf8::calc_bytes_size(str);
    }

    inline usize string::calc_length_impl(const char *str)
    {
        return core_utf8::calc_length(str);
    }
} // namespace deep

#endif
