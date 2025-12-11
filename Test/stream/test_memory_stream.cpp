#include "DeepLib/lib.hpp"
#include "DeepLib/stream/memory_stream.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::uint8 buffer[] = {
        7, 8, 9,
        4, 5, 6,
        1, 2, 3
    };

    deep::uint8 out[sizeof(buffer)];

    deep::memory_stream s = deep::memory_stream(context);

    deep::usize bytes = 0;

    if (!s.write(buffer, sizeof(buffer), &bytes))
    {
        return 10;
    }

    if (bytes != sizeof(buffer))
    {
        return 11;
    }

    s.seek(0, deep::stream::seek_origin::Begin);

    bytes = 0;

    if (!s.read(out, sizeof(out), &bytes))
    {
        return 12;
    }

    if (bytes != sizeof(out))
    {
        return 13;
    }

    deep::usize index;
    for (index = 0; index < sizeof(out); ++index)
    {
        if (out[index] != buffer[index])
        {
            return 14;
        }
    }

    for (index = 0; index < sizeof(out); ++index)
    {
        if (out[index] != s.get()[index])
        {
            return 15;
        }
    }

    return 0;
}
