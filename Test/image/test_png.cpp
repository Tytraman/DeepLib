#include "DeepLib/lib.hpp"
#include "DeepLib/image/png.hpp"
#include "DeepLib/image/image.hpp"
#include "DeepLib/stream/file_stream.hpp"
#include "DeepLib/filesystem/filesystem.hpp"

#include <stdio.h>

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

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
        return 10;
    }

    deep::png p = deep::png::load(context, &input);

    if (!p.is_valid())
    {
        return 11;
    }

    if (!p.check())
    {
        return 12;
    }

    if (!p.read_info())
    {
        return 13;
    }

    deep::image original = p.read_image();

    if (!original.is_valid())
    {
        return 14;
    }

    deep::image horizontal = original.copy(context.get());

    if (!horizontal.is_valid())
    {
        return 15;
    }

    if (!horizontal.apply_horizontal_mirror_effect())
    {
        return 16;
    }

    deep::image vertical = original.copy(context.get());

    if (!vertical.is_valid())
    {
        return 17;
    }

    if (!vertical.apply_vertical_mirror_effect())
    {
        return 18;
    }

    deep::image resize1 = original.copy(context.get());

    if (!resize1.is_valid())
    {
        return 19;
    }

    if (!resize1.resize(3000, 2500))
    {
        return 20;
    }

    deep::image resize2 = original.copy(context.get());

    if (!resize2.is_valid())
    {
        return 21;
    }

    if (!resize2.resize(500, 500))
    {
        return 22;
    }

    deep::file_stream output_horizontal = deep::file_stream(context, DEEP_TEXT_NATIVE("test_output_horizontal.png"),
                                                            deep::core_fs::file_mode::Create,
                                                            deep::core_fs::file_access::Write,
                                                            deep::core_fs::file_share::Read);

    deep::file_stream output_vertical = deep::file_stream(context, DEEP_TEXT_NATIVE("test_output_vertical.png"),
                                                          deep::core_fs::file_mode::Create,
                                                          deep::core_fs::file_access::Write,
                                                          deep::core_fs::file_share::Read);

    deep::file_stream output_resize1 = deep::file_stream(context, DEEP_TEXT_NATIVE("test_output_resize1.png"),
                                                         deep::core_fs::file_mode::Create,
                                                         deep::core_fs::file_access::Write,
                                                         deep::core_fs::file_share::Read);

    deep::file_stream output_resize2 = deep::file_stream(context, DEEP_TEXT_NATIVE("test_output_resize2.png"),
                                                         deep::core_fs::file_mode::Create,
                                                         deep::core_fs::file_access::Write,
                                                         deep::core_fs::file_share::Read);

    if (!output_horizontal.open())
    {
        return 40;
    }

    if (!output_vertical.open())
    {
        return 41;
    }

    if (!output_resize1.open())
    {
        return 42;
    }

    if (!output_resize2.open())
    {
        return 43;
    }

    if (!deep::png::convert(horizontal, &output_horizontal))
    {
        return 50;
    }

    if (!deep::png::convert(vertical, &output_vertical))
    {
        return 51;
    }

    if (!deep::png::convert(resize1, &output_resize1))
    {
        return 52;
    }

    if (!deep::png::convert(resize2, &output_resize2))
    {
        return 53;
    }

    return 0;
}
