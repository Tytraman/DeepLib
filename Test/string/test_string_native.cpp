#include "DeepLib/lib.hpp"
#include "DeepLib/string/string_native.hpp"

#include <stdio.h>

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::string_native str = deep::string_native(context, DEEP_TEXT_NATIVE("Hello "));

    if (!str.is_valid())
    {
        return 10;
    }

    if (str.get_length() != 6)
    {
        return 11;
    }

    if (!str.append(DEEP_TEXT_NATIVE("world ")))
    {
        return 12;
    }

    if (str.get_length() != 12)
    {
        return 13;
    }

    str += DEEP_TEXT_NATIVE("C++");

    deep::usize character_index;

    if (!str.find(DEEP_TEXT_NATIVE('w'), &character_index))
    {
        return 20;
    }

    if (character_index != 6)
    {
        return 21;
    }

    if (!str.find_from_end(DEEP_TEXT_NATIVE('l'), &character_index))
    {
        return 22;
    }

    if (character_index != 9)
    {
        return 23;
    }

    if (!str.shrink(character_index))
    {
        return 24;
    }

    printf("Shrink: %ls\n", *str);

    return 0;
}
