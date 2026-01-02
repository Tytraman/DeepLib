#include "DeepLib/lib.hpp"
#include "DeepLib/filesystem/filesystem.hpp"

#include <stdio.h>

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::string_native str = deep::fs::get_executable_path(context);

    if (!str.is_valid())
    {
        return 10;
    }

    deep::string_native executable_directory = deep::fs::get_executable_directory(context);

    printf("%ls\n%ls\n", *str, *executable_directory);

    return 0;
}
