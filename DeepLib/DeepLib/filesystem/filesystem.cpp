#include "filesystem.hpp"
#include "DeepCore/filesystem.hpp"

namespace deep
{
    string_native fs::get_cwd(const ref<ctx> &context)
    {
        if (context == nullptr)
        {
            return string_native();
        }

        return string_native(context, core_fs::get_current_working_directory(context->get_internal_ctx()));
    }

    string_native fs::get_executable_path(const ref<ctx> &context)
    {
        usize path_bytes_size;
        usize path_length;

        native_char *path = core_fs::get_executable_path(ctx::get_internal_ctx(context.get()), &path_bytes_size, &path_length);

        return string_native(context, path, path_bytes_size, path_length);
    }

    string_native fs::get_executable_directory(const ref<ctx> &context)
    {
        string_native path = get_executable_path(context);

        usize last_separator;

        if (!path.find_from_end(DEEP_NATIVE_SEPARATOR_CHAR, &last_separator))
        {
            return string_native();
        }

        if (!path.shrink(last_separator + 1))
        {
            return string_native();
        }

        return path;
    }
} // namespace deep
