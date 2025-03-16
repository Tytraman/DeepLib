#include "filesystem.hpp"
#include "core.hpp"
#include "error.hpp"
#include "types.hpp"

namespace deep
{
    const char *core_fs::get_current_working_directory()
    {
        return core_get_current_working_directory(core::g_internal_context);
    }

    fd core_fs::open_file(const char *filename, file_mode mode,
                          file_access access, file_share share)
    {
        if (filename == nullptr)
        {
            core::set_internal_context_result(error::EmptyStr);

            return invalid_fd;
        }

        if (to_utype(mode) < to_utype(core_fs::file_mode::Append) ||
            to_utype(mode) > to_utype(core_fs::file_mode::Truncate) ||
            to_utype(access) < to_utype(core_fs::file_access::Read) ||
            to_utype(access) > to_utype(core_fs::file_access::ReadWrite) ||
            to_utype(share) < to_utype(core_fs::file_share::Delete) ||
            to_utype(share) > to_utype(core_fs::file_share::ReadWrite))
        {
            core::set_internal_context_result(error::InvalidEnumValue);

            return invalid_fd;
        }

        return core_open_file(core::set_current_internal_context, filename, mode, access, share);
    }

    bool core_fs::delete_file(const char *filename)
    {
        if (filename == nullptr)
        {
            core::set_internal_context_result(error::EmptyStr);

            return false;
        }

        return core_delete_file(core::set_current_internal_context, filename);
    }
} // namespace deep
