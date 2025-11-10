#include "file_stream.hpp"

namespace deep
{
    file_stream::file_stream(ctx *context, const native_char *filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share)
            : m_filename(context, filename),
              m_mode(mode),
              m_access(access),
              m_share(share),
              m_fd(invalid_fd),
              m_is_opened(false),
              m_context(context)
    {
    }

    file_stream::file_stream(ctx *context, string_native &filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share)
            : m_filename(filename),
              m_mode(mode),
              m_access(access),
              m_share(share),
              m_fd(invalid_fd),
              m_is_opened(false),
              m_context(context)
    {
    }

    file_stream::~file_stream()
    {
        close();
    }

    bool file_stream::open()
    {
        if (m_is_opened)
        {
            return true;
        }

        m_fd = core_fs::open_file(ctx::get_internal_ctx(m_context), *m_filename, m_mode, m_access, m_share);

        if (m_fd == invalid_fd)
        {
            return false;
        }

        m_is_opened = true;

        return true;
    }

    bool file_stream::close()
    {
        if (!m_is_opened)
        {
            return false;
        }

        if (!core_fs::close_file(ctx::get_internal_ctx(m_context), m_fd))
        {
            return false;
        }

        m_fd        = invalid_fd;
        m_is_opened = false;

        return true;
    }

    bool file_stream::flush()
    {
        if (!m_is_opened)
        {
            return false;
        }

        return core_fs::flush_file(ctx::get_internal_ctx(m_context), m_fd);
    }

    bool file_stream::can_read() const
    {
        return m_access == core_fs::file_access::Read ||
               m_access == core_fs::file_access::ReadWrite;
    }

    bool file_stream::can_write() const
    {
        return m_access == core_fs::file_access::Write ||
               m_access == core_fs::file_access::ReadWrite;
    }

    bool file_stream::can_timeout() const
    {
        return false;
    }

    bool file_stream::can_seek() const
    {
        return true;
    }

    usize file_stream::get_length() const
    {
        if (!m_is_opened)
        {
            return 0;
        }

        usize size = 0;

        if (!core_fs::get_file_size(ctx::get_internal_ctx(m_context), m_fd, &size))
        {
            return 0;
        }

        return size;
    }

    bool file_stream::set_length(usize length)
    {
        if (!m_is_opened)
        {
            return 0;
        }

        return core_fs::set_file_size(ctx::get_internal_ctx(m_context), m_fd, length);
    }

    usize file_stream::get_position() const
    {
        if (!m_is_opened)
        {
            return 0;
        }

        usize size = 0;

        if (!core_fs::get_file_position(ctx::get_internal_ctx(m_context), m_fd, &size))
        {
            return 0;
        }

        return size;
    }

    uint32 file_stream::get_read_timeout() const
    {
        return 0;
    }

    uint32 file_stream::get_write_timeout() const
    {
        return 0;
    }

    void file_stream::set_read_timeout(uint32 /* value */)
    {
    }

    void file_stream::set_write_timeout(uint32 /* value */)
    {
    }

    usize file_stream::seek(isize offset, seek_origin origin)
    {
        if (!m_is_opened)
        {
            return 0;
        }

        core_fs::seek_origin or ;

        switch (origin)
        {
            default:
                return false;
            case seek_origin::Begin:
            {
                or = core_fs::seek_origin::Begin;
            }
            break;
            case seek_origin::Current:
            {
                or = core_fs::seek_origin::Current;
            }
            break;
            case seek_origin::End:
            {
                or = core_fs::seek_origin::End;
            }
            break;
        }

        usize new_size;

        if (!core_fs::seek_file(ctx::get_internal_ctx(m_context), m_fd, offset, or, &new_size))
        {
            return 0;
        }

        return new_size;
    }

    bool file_stream::read(void *dest, usize count, usize *bytes_read)
    {
        if (!m_is_opened)
        {
            return false;
        }

        return core_fs::read_file(ctx::get_internal_ctx(m_context), m_fd, count, dest, bytes_read);
    }

    bool file_stream::write(void *src, usize count, usize *bytes_written)
    {
        if (!m_is_opened)
        {
            return false;
        }

        return core_fs::write_file(ctx::get_internal_ctx(m_context), m_fd, count, src, bytes_written);
    }

    bool file_stream::copy_to(stream &other)
    {
        static constexpr usize max_bytes = 4096;

        usize position = 0;
        usize length   = 0;
        usize diff;
        usize bytes_read       = 0;
        void *internal_context = ctx::get_internal_ctx(m_context);

        if (!m_is_opened)
        {
            return false;
        }

        if (!core_fs::get_file_position(internal_context, m_fd, &position))
        {
            return false;
        }

        if (!core_fs::get_file_size(internal_context, m_fd, &length))
        {
            return false;
        }

        // Il ne reste plus rien à lire.
        if (position >= length)
        {
            return true;
        }

        diff = length - position;

        buffer_ptr<uint8> buffer = mem::alloc_buffer<uint8>(m_context, diff);

        if (!buffer.is_valid())
        {
            return false;
        }

        if (!core_fs::read_file(internal_context, m_fd, diff, buffer.get(), &bytes_read))
        {
            mem::dealloc_buffer(buffer);

            return false;
        }

        if (!other.write(buffer.get(), bytes_read, nullptr))
        {
            mem::dealloc_buffer(buffer);

            return false;
        }

        mem::dealloc_buffer(buffer);

        other.flush();

        return true;
    }

    bool file_stream::is_opened() const
    {
        return m_is_opened;
    }

} // namespace deep
