#include "filesystem.hpp"
#include "context.hpp"
#include "error.hpp"
#include "types.hpp"

namespace deep
{
    const native_char *core_fs::get_current_working_directory(void *internal_context)
    {
        return core_get_current_working_directory(internal_context);
    }

    fd core_fs::open_file(void *internal_context, const native_char *filename, file_mode mode,
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

    bool core_fs::close_file(void *internal_context, fd file_descriptor)
    {
        return core_close_file(internal_context, file_descriptor);
    }

    bool core_fs::flush_file(void *internal_context, fd file_descriptor)
    {
        return core_flush_file(internal_context, file_descriptor);
    }

    bool core_fs::seek_file(void *internal_context, fd file_descriptor, isize offset, seek_origin origin, usize *new_size)
    {
        return core_seek_file(internal_context, file_descriptor, offset, origin, new_size);
    }

    bool core_fs::delete_file(void *internal_context, const native_char *filename)
    {
        if (filename == nullptr)
        {
            core_ctx::set_internal_ctx_result(internal_context, error::EmptyStr);

            return false;
        }

        return core_delete_file(internal_context, filename);
    }

    bool core_fs::read_file(void *internal_context, fd file_descriptor, usize count, void *dest, usize *bytes_read)
    {
        return core_read_file(internal_context, file_descriptor, count, dest, bytes_read);
    }

    bool core_fs::write_file(void *internal_context, fd file_descriptor, usize count, const void *from, usize *bytes_written)
    {
        return core_write_file(internal_context, file_descriptor, count, from, bytes_written);
    }

    bool core_fs::get_file_size(void *internal_context, fd file_descriptor, usize *dest)
    {
        return core_get_file_size(internal_context, file_descriptor, dest);
    }

    bool core_fs::set_file_size(void *internal_context, fd file_descriptor, usize size)
    {
        return core_set_file_size(internal_context, file_descriptor, size);
    }

    bool core_fs::get_file_position(void *internal_context, fd file_descriptor, usize *dest)
    {
        return core_get_file_position(internal_context, file_descriptor, dest);
    }

    native_char *core_fs::get_executable_path(void *internal_context, usize *path_bytes_size, usize *path_length)
    {
        return core_get_executable_path(internal_context, path_bytes_size, path_length);
    }
} // namespace deep
