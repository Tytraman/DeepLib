#ifndef DEEP_LIB_NATIVE_STRING_HPP
#define DEEP_LIB_NATIVE_STRING_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/string/string_base.hpp"

#include <cmath>

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

        static string_native from_impl(ctx *context, bool value);
        static string_native from_impl(ctx *context, int64 value);
        static string_native from_impl(ctx *context, uint64 value);
        static string_native from_impl(ctx *context, double value);
    };

    inline usize string_native::calc_bytes_size_impl(const native_char *str)
    {
        return DEEP_TEXT_NATIVE_BYTES_SIZE(str);
    }

    inline usize string_native::calc_length_impl(const native_char *str)
    {
        return DEEP_TEXT_NATIVE_LENGTH(str);
    }

    inline string_native string_native::from_impl(ctx *context, bool value)
    {
        string_native str = string_native(context);

        switch (value)
        {
            case false:
            {
                str = string_native(context, DEEP_TEXT_NATIVE("false"));
            }
            break;
            case true:
            {
                str = string_native(context, DEEP_TEXT_NATIVE("true"));
            }
            break;
        }

        return str;
    }

    inline string_native string_native::from_impl(ctx *context, int64 value)
    {
        string_native str = string_native(context);

        auto ab = std::abs(value);

        if (value > -10 && value < 10)
        {
            if (value < 0)
            {
                str.append(DEEP_TEXT_NATIVE('-'));
            }

            str.append(static_cast<native_char>(ab + '0'));

            return str;
        }

        while (ab != 0)
        {
            str.insert(static_cast<native_char>(ab % 10 + '0'));
            ab /= 10;
        }

        if (value < 0)
        {
            str.insert(DEEP_TEXT_NATIVE('-'));
        }

        return str;
    }

    inline string_native string_native::from_impl(ctx *context, uint64 value)
    {
        string_native str = string_native(context);

        if (value < 10)
        {
            str.append(static_cast<native_char>(value + '0'));

            return str;
        }

        while (value != 0)
        {
            str.insert(static_cast<native_char>(value % 10 + '0'));
            value /= 10;
        }

        return str;
    }

    inline string_native string_native::from_impl(ctx *context, double value)
    {
        string_native str = string_native(context);

        // Récupère la partie entière.
        double integer;
        double decimal = std::modf(value, &integer);
        integer        = std::abs(integer);

        if (value > -10.0 && value < 10.0)
        {
            if (value < 0.0)
            {
                str.append(DEEP_TEXT_NATIVE('-'));
            }

            str.append(static_cast<native_char>(static_cast<uint8>(integer) + '0'));
        }
        else
        {
            uint64 copy = static_cast<uint64>(integer);

            while (copy != 0)
            {
                str.insert(static_cast<native_char>(copy % 10 + '0'));
                copy /= 10;
            }

            if (value < 0)
            {
                str.insert(DEEP_TEXT_NATIVE('-'));
            }
        }

        str.append(DEEP_TEXT_NATIVE('.'));

        if (decimal == 0.0)
        {
            str.append(DEEP_TEXT_NATIVE('0'));

            return str;
        }

        while (decimal != 0.0)
        {
            decimal *= 10;
            decimal = std::modf(decimal, &integer);
            integer = std::abs(integer);

            str.append(static_cast<native_char>(static_cast<uint8>(integer) + '0'));
        }

        return str;
    }
} // namespace deep

#endif
