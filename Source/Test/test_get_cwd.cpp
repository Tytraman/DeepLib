#include "context.hpp"
#include "filesystem.hpp"

#include <stdio.h>

int main(int argc, char *argv[])
{
    deep::ctx context;

    const char *cwd = deep::fs::get_current_working_directory(context);

    if (cwd != nullptr)
    {
        printf("cwd: %s\n", cwd);

        return 0;
    }

    return 1;
}
