#include "memory_stream.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/maths/math.hpp"

namespace deep
{
    memory_stream::memory_stream(const ref<ctx> &context)
            : stream(context), m_buffer(context.get(), nullptr, 0), m_position(0)
    {
    }

    bool memory_stream::open()
    {
        return true;
    }

    bool memory_stream::close()
    {
        m_buffer.destroy();
        m_position = 0;

        return true;
    }

    bool memory_stream::flush()
    {
        return true;
    }

    bool memory_stream::can_read() const
    {
        return true;
    }

    bool memory_stream::can_write() const
    {
        return true;
    }

    bool memory_stream::can_timeout() const
    {
        return false;
    }

    bool memory_stream::can_seek() const
    {
        return true;
    }

    usize memory_stream::get_length() const
    {
        return m_buffer.get_bytes_size();
    }

    bool memory_stream::set_length(usize length)
    {
        return mem::realloc(m_buffer, length);
    }

    usize memory_stream::get_position() const
    {
        return m_position;
    }

    uint32 memory_stream::get_read_timeout() const
    {
        return 0;
    }

    uint32 memory_stream::get_write_timeout() const
    {
        return 0;
    }

    void memory_stream::set_read_timeout(uint32)
    {
    }

    void memory_stream::set_write_timeout(uint32)
    {
    }

    usize memory_stream::seek(isize offset, seek_origin origin)
    {
        switch (origin)
        {
            default:
                break;
            case seek_origin::Begin:
            {
                if (offset <= 0)
                {
                    m_position = 0;
                }
                else
                {
                    usize max = get_length();
                    if (static_cast<usize>(offset) >= max)
                    {
                        if (max > 0)
                        {
                            m_position = max - 1;
                        }
                        else
                        {
                            m_position = 0;
                        }
                    }
                }
            }
            break;
            case seek_origin::Current:
            {
                if (offset < 0)
                {
                    if (math::abs(offset) >= m_position)
                    {
                        m_position = 0;

                        break;
                    }
                }

                m_position += make_unsigned<isize>(offset);
            }
            break;
            case seek_origin::End:
            {
                if (offset >= 0)
                {
                    break;
                }

                usize length = get_length();

                if (math::abs(offset) >= length)
                {
                    m_position = 0;
                }
                else
                {
                    m_position += make_unsigned<isize>(offset);
                }
            }
            break;
        }

        return m_position;
    }

    bool memory_stream::read(void *dest, usize count, usize *bytes_read)
    {
        usize position = m_position;
        usize length   = get_length();
        usize target_position;

        // S'il n'y a aucun octet à lire.
        if (position >= length)
        {
            if (bytes_read != nullptr)
            {
                *bytes_read = 0;
            }

            return true;
        }

        target_position = position + count;

        // Si la quantité d'octets à lire dépasse le nombre d'octets restants,
        // ne lit que les octets restants.
        if (target_position > length)
        {
            count -= target_position - length;
        }

        memcpy(dest, &m_buffer[position], count);

        m_position += count;

        if (bytes_read != nullptr)
        {
            *bytes_read = count;
        }

        return true;
    }

    bool memory_stream::write(const void *src, usize count, usize *bytes_written)
    {
        usize position = m_position;
        usize length   = get_length();

        usize target_position = position + count;

        if (target_position > length)
        {
            if (!mem::realloc(m_buffer, target_position))
            {
                return false;
            }
        }

        memcpy(m_buffer.get(), src, count);

        m_position += count;

        if (bytes_written != nullptr)
        {
            *bytes_written = count;
        }

        return true;
    }

    bool memory_stream::copy_to(stream &other)
    {
        if (!other.can_write())
        {
            return false;
        }

        usize position = m_position;
        usize length   = get_length();
        usize diff;

        // Il ne reste plus rien à lire.
        if (position >= length)
        {
            return true;
        }

        diff = length - position;

        if (!other.write(&m_buffer[position], diff, nullptr))
        {
            return false;
        }

        m_position = length;

        return true;
    }

    bool memory_stream::is_opened() const
    {
        return true;
    }

} // namespace deep
