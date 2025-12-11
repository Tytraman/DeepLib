#include <DeepCore/filesystem.hpp>
#include <DeepLib/lib.hpp>

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    const deep::native_char *cwd = deep::core_fs::get_current_working_directory(context->get_internal_ctx());

    if (cwd == nullptr)
    {
        return 2;
    }

    return 0;
}
