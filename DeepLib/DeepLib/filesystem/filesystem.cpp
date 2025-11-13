#include "filesystem.hpp"

#include "DeepCore/filesystem.hpp"

namespace deep
{
    string_native fs::get_cwd(ctx *context)
    {
        if (context == nullptr)
        {
            return string_native(nullptr);
        }

        return string_native(context, core_fs::get_current_working_directory(context->get_internal_ctx()));
    }
} // namespace deep
