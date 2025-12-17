#include "DeepLib/lib.hpp"
#include "DeepLib/image/png.hpp"
#include "DeepLib/image/image.hpp"
#include "DeepLib/stream/file_stream.hpp"
#include "DeepLib/filesystem/filesystem.hpp"

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

    deep::file_stream input = deep::file_stream(context, DEEP_TEXT_NATIVE("test_input_luminance.png"),
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

    deep::image palette = p.read_image();

    if (!palette.is_valid())
    {
        return 14;
    }

    if (!palette.apply_luminance())
    {
        return 20;
    }

    deep::file_stream output = deep::file_stream(context, DEEP_TEXT_NATIVE("test_output_luminance.png"),
                                                 deep::core_fs::file_mode::Create,
                                                 deep::core_fs::file_access::Write,
                                                 deep::core_fs::file_share::Read);

    if (!output.open())
    {
        return 40;
    }

    if (!deep::png::convert(palette, &output))
    {
        return 50;
    }

    return 0;
}
