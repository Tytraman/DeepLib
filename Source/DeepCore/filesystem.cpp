#include "filesystem.hpp"
#include "error.hpp"
#include "types.hpp"
#include <unistd.h>

namespace deep
{
    const_path_str fs::get_current_working_directory(ctx &context)
    {
        return core_get_current_working_directory(context);
    }

    fd fs::open_file(ctx &context, const path_str filename, file_mode mode,
                     file_access access, file_share share)
    {
        if (filename == nullptr)
        {
            context.result = error::EmptyStr;

            return invalid_fd;
        }

        if (to_utype(mode) < to_utype(fs::file_mode::Append) ||
            to_utype(mode) > to_utype(fs::file_mode::Truncate) ||
            to_utype(access) < to_utype(fs::file_access::Read) ||
            to_utype(access) > to_utype(fs::file_access::ReadWrite) ||
            to_utype(share) < to_utype(fs::file_share::Delete) ||
            to_utype(share) > to_utype(fs::file_share::ReadWrite))
        {
            context.result = error::InvalidEnumValue;

            return invalid_fd;
        }

        return core_open_file(context, filename, mode, access, share);
    }

    bool delete_file(ctx &context, const path_str filename)
    {
        if (filename == nullptr)
        {
            context.result = error::EmptyStr;
        }

        return core_delete_file(context, filename);
    }

} // namespace deep
