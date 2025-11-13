#include "DeepLib/lib.hpp"
#include "DeepLib/image/png.hpp"
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

        deep::png image = deep::png::load(context, &input);

        if (!image.is_valid())
        {
            return 3;
        }

        if (!image.check())
        {
            return 4;
        }

        if (!image.read_info())
        {
            return 5;
        }

        deep::uint32 width   = image.get_width();
        deep::uint32 height  = image.get_height();
        deep::uint8 channels = image.get_channels();

        printf("Image info:\n"
               "  Width: %u\n"
               "  Height: %u\n"
               "  Channels: %u\n",
               width, height, channels);

        if (!image.read_image())
        {
            return 6;
        }
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
