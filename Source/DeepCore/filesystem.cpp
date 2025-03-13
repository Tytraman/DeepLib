#include "filesystem.hpp"
#include "core.hpp"
#include "error.hpp"
#include "types.hpp"

namespace deep
{
    const char *fs::get_current_working_directory()
    {
        return core_get_current_working_directory(&core::g_current_context->result);
    }

    fd fs::open_file(const char *filename, file_mode mode,
                     file_access access, file_share share)
    {
        if (filename == nullptr)
        {
            core::g_current_context->result = error::EmptyStr;

            return invalid_fd;
        }

        if (to_utype(mode) < to_utype(fs::file_mode::Append) ||
            to_utype(mode) > to_utype(fs::file_mode::Truncate) ||
            to_utype(access) < to_utype(fs::file_access::Read) ||
            to_utype(access) > to_utype(fs::file_access::ReadWrite) ||
            to_utype(share) < to_utype(fs::file_share::Delete) ||
            to_utype(share) > to_utype(fs::file_share::ReadWrite))
        {
            core::g_current_context->result = error::InvalidEnumValue;

            return invalid_fd;
        }

        return core_open_file(&core::g_current_context->result, filename, mode, access, share);
    }

    bool fs::delete_file(const char *filename)
    {
        if (filename == nullptr)
        {
            core::g_current_context->result = error::EmptyStr;
        }

        return core_delete_file(&core::g_current_context->result, filename);
    }

} // namespace deep
