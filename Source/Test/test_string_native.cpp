#include "lib.hpp"
#include "string/string_native.hpp"

#include <stdio.h>

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    {
        deep::string_native str = deep::string_native(context, DEEP_TEXT_NATIVE("Hello "));

        if (!str.is_valid())
        {
            return 2;
        }

        if (str.get_length() != 6)
        {
            return 3;
        }

        if (!str.append(DEEP_TEXT_NATIVE("world ")))
        {
            return 4;
        }

        if (str.get_length() != 12)
        {
            return 5;
        }

        deep::string_native &other = str += DEEP_TEXT_NATIVE("C++");
        if (other.get_length() != 15)
        {
            return 6;
        }

        if (other.encoding == deep::string_encoding::Unicode)
        {
            if (other.get_bytes_size() != 32)
            {
                return 7;
            }

            printf("%ls", *other);
        }
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
