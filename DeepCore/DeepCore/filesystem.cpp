#include "filesystem.hpp"
#include "context.hpp"
#include "error.hpp"
#include "types.hpp"

namespace deep
{
    const char *core_fs::get_current_working_directory(void *internal_context)
    {
        return core_get_current_working_directory(internal_context);
    }

    fd core_fs::open_file(void *internal_context, const char *filename, file_mode mode,
                          file_access access, file_share share)
    {
        if (filename == nullptr)
        {
            core_ctx::set_internal_ctx_result(internal_context, error::EmptyStr);

            return invalid_fd;
        }

        if (to_utype(mode) < to_utype(core_fs::file_mode::Append) ||
            to_utype(mode) > to_utype(core_fs::file_mode::Truncate) ||
            to_utype(access) < to_utype(core_fs::file_access::Read) ||
            to_utype(access) > to_utype(core_fs::file_access::ReadWrite) ||
            to_utype(share) < to_utype(core_fs::file_share::Delete) ||
            to_utype(share) > to_utype(core_fs::file_share::ReadWrite))
        {
            core_ctx::set_internal_ctx_result(internal_context, error::InvalidEnumValue);

            return invalid_fd;
        }

        return core_open_file(internal_context, filename, mode, access, share);
    }

    bool core_fs::delete_file(void *internal_context, const char *filename)
    {
        if (filename == nullptr)
        {
            core_ctx::set_internal_ctx_result(internal_context, error::EmptyStr);

            return false;
        }

        return core_delete_file(internal_context, filename);
    }
} // namespace deep
