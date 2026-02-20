#include <DeepCore/filesystem.hpp>
#include <DeepLib/lib.hpp>

#include <stdio.h>

int main(int /*argc*/, char * /*argv*/[])
{
    printf("Creating context...\n");
    fflush(stdout);

    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    printf("Context created\n");
    fflush(stdout);

    if (!context.is_valid())
    {
        fprintf(stderr, "context is invalid\n");

        return 1;
    }

    const deep::native_char *cwd = deep::core_fs::get_current_working_directory(context->get_internal_ctx());

    if (cwd == nullptr)
    {
        fprintf(stderr, "cwd is null\n");

        return 2;
    }

    printf("cwd: %ls\n", cwd);
    fflush(stdout);

    return 0;
}
