#include "context.hpp"
#include "filesystem.hpp"

#include <stdio.h>

int main(int argc, char *argv[])
{
    deep::ctx context;

    const char *cwd = deep::fs::get_current_working_directory(context);

    if (cwd == nullptr)
    {
        return 1;
    }

    return 0;
}
