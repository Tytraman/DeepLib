#include "text_writer.hpp"
#include "DeepLib/context.hpp"

namespace deep
{

    text_writer &text_writer::operator<<(bool value)
    {
        write(value);

        return *this;
    }

    text_writer &text_writer::operator<<(const char *str)
    {
        write(str);

        return *this;
    }

    text_writer &text_writer::operator<<(int32 value)
    {
        write(value);

        return *this;
    }

    text_writer &text_writer::operator<<(uint32 value)
    {
        write(value);

        return *this;
    }

    text_writer &text_writer::operator<<(int64 value)
    {
        write(value);

        return *this;
    }

    text_writer &text_writer::operator<<(uint64 value)
    {
        write(value);

        return *this;
    }

    text_writer &text_writer::operator<<(double value)
    {
        write(value);

        return *this;
    }
} // namespace deep
