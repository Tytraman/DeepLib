#ifndef DEEP_LIB_NATIVE_STRING_HPP
#define DEEP_LIB_NATIVE_STRING_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/string/string_base.hpp"

namespace deep
{
    template class DEEP_LIB_API ref<buffer_primitive<native_char>>;

    class DEEP_LIB_API string_native : public string_base<string_native, native_char>
    {
      public:
        using string_base<string_native, native_char>::string_base;

        static constexpr string_encoding encoding = DEEP_NATIVE_ENCODING;

        static usize calc_bytes_size_impl(const native_char *str);
        static usize calc_length_impl(const native_char *str);
    };

    inline usize string_native::calc_bytes_size_impl(const native_char *str)
    {
        return DEEP_TEXT_NATIVE_BYTES_SIZE(str);
    }

    inline usize string_native::calc_length_impl(const native_char *str)
    {
        return DEEP_TEXT_NATIVE_LENGTH(str);
    }
} // namespace deep

#endif
