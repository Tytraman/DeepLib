#include "DeepLib/lib.hpp"
#include "DeepLib/string/string.hpp"

#include <stdio.h>

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    {
        deep::string str = deep::string(context, DEEP_STRING("Hello "));

        if (!str.is_valid())
        {
            return 2;
        }

        if (str.get_length() != 6)
        {
            return 3;
        }

        str += DEEP_STRING("wérld");

        if (str.get_length() != 11)
        {
            return 4;
        }

        printf("%s", *str);
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
