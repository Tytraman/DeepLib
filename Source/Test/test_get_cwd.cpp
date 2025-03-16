#include "DeepCore/filesystem.hpp"
#include "lib.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    if (!deep::lib::create_context(context))
    {
        return 1;
    }

    const char *cwd = deep::core_fs::get_current_working_directory();

    if (cwd == nullptr)
    {
        return 1;
    }

    if (!deep::lib::destroy_context())
    {
        return 1;
    }

    return 0;
}
