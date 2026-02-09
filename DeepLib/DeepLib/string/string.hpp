#ifndef DEEP_LIB_STRING_HPP
#define DEEP_LIB_STRING_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/string/utf8.hpp"
#include "DeepLib/string/string_base.hpp"
#include "DeepLib/maths/math.hpp"

#include <cmath>

namespace deep
{
    template class DEEP_LIB_API ref<buffer_primitive<char>>;

    class DEEP_LIB_API string : public string_base<string, char>
    {
      public:
        using string_base<string, char>::string_base;

        static constexpr string_encoding encoding = string_encoding::UTF8;

        static uint64 hash(const char *str);

        static usize calc_bytes_size_impl(const char *str);
        static usize calc_length_impl(const char *str);

        static string from_impl(const ref<ctx> &context, bool value);
        static string from_impl(const ref<ctx> &context, int64 value);
        static string from_impl(const ref<ctx> &context, uint64 value);
        static string from_impl(const ref<ctx> &context, double value, int16 digits);
    };

    inline usize deep::string::calc_bytes_size_impl(const char *str)
    {
        return core_utf8::calc_bytes_size(str);
    }

    inline usize string::calc_length_impl(const char *str)
    {
        return core_utf8::calc_length(str);
    }

    inline string string::from_impl(const ref<ctx> &context, bool value)
    {
        string str = string(context);

        switch (value)
        {
            case false:
            {
                str = string(context, DEEP_TEXT_UTF8("false"));
            }
            break;
            case true:
            {
                str = string(context, DEEP_TEXT_UTF8("true"));
            }
            break;
        }

        return str;
    }

    inline string string::from_impl(const ref<ctx> &context, int64 value)
    {
        string str = string(context);

        uint64 ab = math::abs(value);

        if (value > -10 && value < 10)
        {
            if (value < 0)
            {
                str.append('-');
            }

            str.append(static_cast<char>(ab + '0'));

            return str;
        }

        while (ab != 0)
        {
            str.insert(ab % 10 + '0');
            ab /= 10;
        }

        if (value < 0)
        {
            str.insert('-');
        }

        return str;
    }

    inline string string::from_impl(const ref<ctx> &context, uint64 value)
    {
        string str = string(context);

        if (value < 10)
        {
            str.append(static_cast<char>(value + '0'));

            return str;
        }

        while (value != 0)
        {
            str.insert(value % 10 + '0');
            value /= 10;
        }

        return str;
    }

    inline string string::from_impl(const ref<ctx> &context, double value, int16 digits)
    {
        string str = string(context);

        // Récupère la partie entière.
        double integer;
        double decimal = std::modf(value, &integer);
        integer        = std::abs(integer);

        if (value > -10.0 && value < 10.0)
        {
            if (value < 0.0)
            {
                str.append('-');
            }

            str.append(static_cast<char>(static_cast<uint8>(integer) + '0'));
        }
        else
        {
            uint64 copy = static_cast<uint64>(integer);

            while (copy != 0)
            {
                str.insert(copy % 10 + '0');
                copy /= 10;
            }

            if (value < 0)
            {
                str.insert('-');
            }
        }

        str.append(DEEP_TEXT_UTF8('.'));

        if (decimal == 0.0)
        {
            str.append(DEEP_TEXT_UTF8('0'));

            return str;
        }

        int16 counter = 0;

        while (decimal != 0.0)
        {
            if (digits >= 0)
            {
                if (counter == digits)
                {
                    break;
                }

                counter++;
            }

            decimal *= 10;
            decimal = std::modf(decimal, &integer);
            integer = std::abs(integer);

            str.append(static_cast<char>(static_cast<uint8>(integer) + '0'));
        }

        return str;
    }
} // namespace deep

#endif
