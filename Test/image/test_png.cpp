#include "DeepLib/lib.hpp"
#include "DeepLib/image/png.hpp"
#include "DeepLib/image/image.hpp"
#include "DeepLib/stream/file_stream.hpp"
#include "DeepLib/filesystem/filesystem.hpp"

#include <stdio.h>

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    {
        deep::string_native cwd = deep::fs::get_cwd(context);

        printf("CWD: %ls\n", *cwd);

        deep::string libpng_version = deep::png::get_libpng_version(context);

        printf("libpng version: %s\n", *libpng_version);

        deep::file_stream input = deep::file_stream(context, DEEP_TEXT_NATIVE("test_input.png"),
                                                    deep::core_fs::file_mode::Open,
                                                    deep::core_fs::file_access::Read,
                                                    deep::core_fs::file_share::Read);

        if (!input.open())
        {
            return 2;
        }

        deep::png p = deep::png::load(context, &input);

        if (!p.is_valid())
        {
            return 3;
        }

        if (!p.check())
        {
            return 4;
        }

        if (!p.read_info())
        {
            return 5;
        }

        deep::image img = p.read_image();

        if (!img.is_valid())
        {
            return 6;
        }

        deep::file_stream output = deep::file_stream(context, DEEP_TEXT_NATIVE("test_output.png"),
                                                     deep::core_fs::file_mode::Create,
                                                     deep::core_fs::file_access::Write,
                                                     deep::core_fs::file_share::Read);

        if (!output.open())
        {
            return 7;
        }

        if (!deep::png::convert(img, &output))
        {
            return 8;
        }
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
