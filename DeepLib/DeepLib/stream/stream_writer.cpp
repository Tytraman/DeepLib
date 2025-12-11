#include "stream_writer.hpp"
#include "DeepLib/string/string.hpp"

namespace deep
{
    stream_writer::stream_writer(stream *s)
            : text_writer(),
              m_stream(s != nullptr ? s->get_context() : ref<ctx>(), s)
    {
    }

    bool stream_writer::open()
    {
        if (!m_stream.is_valid())
        {
            return false;
        }

        return m_stream->open();
    }

    bool stream_writer::close()
    {
        if (!m_stream.is_valid())
        {
            return false;
        }

        return m_stream->close();
    }

    bool stream_writer::write(bool value)
    {
        if (!m_stream.is_valid() || !m_stream->can_write())
        {
            return false;
        }

        string str = string::from(get_context(), value);

        usize bytes_written;

        return m_stream->write(*str, str.get_bytes_size(), &bytes_written);
    }

    bool stream_writer::write(const char *str)
    {
        if (!m_stream.is_valid() || !m_stream->can_write())
        {
            return false;
        }

        usize length = string::calc_bytes_size(str);
        usize bytes_written;

        return m_stream->write(str, length, &bytes_written);
    }

    bool stream_writer::write(int32 value)
    {
        return write(DEEP_I64(value));
    }

    bool stream_writer::write(uint32 value)
    {
        return write(DEEP_U64(value));
    }

    bool stream_writer::write(int64 value)
    {
        if (!m_stream.is_valid() || !m_stream->can_write())
        {
            return false;
        }

        string str = string::from(get_context(), value);

        usize bytes_written;

        return m_stream->write(*str, str.get_bytes_size(), &bytes_written);
    }

    bool stream_writer::write(uint64 value)
    {
        if (!m_stream.is_valid() || !m_stream->can_write())
        {
            return false;
        }

        string str = string::from(get_context(), value);

        usize bytes_written;

        return m_stream->write(*str, str.get_bytes_size(), &bytes_written);
    }

    bool stream_writer::write(double value)
    {
        if (!m_stream.is_valid() || !m_stream->can_write())
        {
            return false;
        }

        string str = string::from(get_context(), value);

        usize bytes_written;

        return m_stream->write(*str, str.get_bytes_size(), &bytes_written);
    }

    bool stream_writer::is_opened()
    {
        if (!m_stream.is_valid())
        {
            return false;
        }

        return m_stream->is_opened();
    }
} // namespace deep
