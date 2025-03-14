#include "core.hpp"
#include "filesystem.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    if (!deep::core::core::create_context(context))
    {
        return 1;
    }

    const char *cwd = deep::core::fs::get_current_working_directory();

    if (cwd == nullptr)
    {
        return 1;
    }

    return 0;
}
