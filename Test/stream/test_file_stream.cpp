#include "DeepLib/lib.hpp"
#include "DeepLib/stream/file_stream.hpp"

#include <stdio.h>
#include <string.h>

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::string_native filename = deep::string_native(context, DEEP_TEXT_NATIVE("test_file_stream.txt"));

    deep::file_stream os = deep::file_stream(context, filename,
                                             deep::core_fs::file_mode::Create,
                                             deep::core_fs::file_access::Write,
                                             deep::core_fs::file_share::Read);

    if (!os.open())
    {
        return 10;
    }

    char text[]            = "Hello World!";
    char out[sizeof(text)] = { 0 };
    deep::usize bytes      = 0;

    if (!os.write(text, sizeof(text) - 1, &bytes))
    {
        return 11;
    }

    if (bytes != sizeof(text) - 1)
    {
        return 12;
    }

    bytes = 0;

    if (!os.close())
    {
        return 5;
    }

    deep::file_stream is = deep::file_stream(context, filename,
                                             deep::core_fs::file_mode::Open,
                                             deep::core_fs::file_access::Read,
                                             deep::core_fs::file_share::Read);

    if (!is.open())
    {
        return 13;
    }

    if (!is.read(out, sizeof(text) - 1, &bytes))
    {
        return 14;
    }

    if (bytes != sizeof(text) - 1)
    {
        return 15;
    }

    out[sizeof(out) - 1] = '\0';

    if (strcmp(text, out) != 0)
    {
        return 16;
    }

    printf("%s\n", out);

    if (is.get_ref_count() != 0)
    {
        return 17;
    }

    return 0;
}
