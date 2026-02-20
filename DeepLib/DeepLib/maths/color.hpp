#ifndef DEEP_LIB_COLOR_HPP
#define DEEP_LIB_COLOR_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/maths/vec3.hpp"

namespace deep
{
    using color_rgb            = vec3<uint8>;
    using color_linearized_rgb = vec3<float>;

#define DEEP_DECLARE_COLOR(__name, __r, __g, __b) inline constexpr color_rgb __name = color_rgb(DEEP_U8(__r), DEEP_U8(__g), DEEP_U8(__b))

    namespace color
    {
        DEEP_LIB_API float srgb_to_linear_channel(float norm_value);
        DEEP_LIB_API uint8 linear_to_srgb_channel(float value);
        DEEP_LIB_API color_rgb find_closest_color(const color_rgb &color, const color_rgb *colors, usize number_of_colors);
        DEEP_LIB_API color_linearized_rgb linearise(const color_rgb &color);
        DEEP_LIB_API color_rgb delinearise(const color_linearized_rgb &color);
        DEEP_LIB_API float calc_luminance(const color_linearized_rgb &color);

        DEEP_DECLARE_COLOR(Black, 0, 0, 0);

        // --- Blanc ---

        DEEP_DECLARE_COLOR(White, 255, 255, 255);
        DEEP_DECLARE_COLOR(AntiFlashWhite, 242, 243, 244);
        DEEP_DECLARE_COLOR(AntiqueWhite, 250, 235, 215);
        DEEP_DECLARE_COLOR(Beige, 245, 245, 220);

        // --- Rouge ---

        DEEP_DECLARE_COLOR(Red, 255, 0, 0);
        DEEP_DECLARE_COLOR(AlizarinCrimson, 227, 38, 54);
        DEEP_DECLARE_COLOR(Amaranth, 229, 43, 80);
        DEEP_DECLARE_COLOR(AmericanRose, 255, 3, 62);
        DEEP_DECLARE_COLOR(Awesome, 255, 32, 82);
        DEEP_DECLARE_COLOR(Bittersweet, 254, 111, 94);
        DEEP_DECLARE_COLOR(CGRed, 224, 60, 49);
        DEEP_DECLARE_COLOR(CadmiumRed, 227, 0, 34);
        DEEP_DECLARE_COLOR(Carmine, 255, 0, 64);
        DEEP_DECLARE_COLOR(CarminePink, 235, 76, 66);
        DEEP_DECLARE_COLOR(CarmineRed, 255, 0, 56);

        // --- Bleu ---

        DEEP_DECLARE_COLOR(Blue, 0, 0, 255);
        DEEP_DECLARE_COLOR(AliceBlue, 240, 248, 255);
        DEEP_DECLARE_COLOR(Aqua, 0, 255, 255);
        DEEP_DECLARE_COLOR(Aquamarine, 127, 255, 212);
        DEEP_DECLARE_COLOR(Azure, 0, 127, 255);

        // --- Vert ---

        DEEP_DECLARE_COLOR(Green, 0, 255, 0);
        DEEP_DECLARE_COLOR(AndroidGreen, 164, 198, 57);
        DEEP_DECLARE_COLOR(Ao, 0, 128, 0);
        DEEP_DECLARE_COLOR(AppleGreen, 141, 182, 0);
    }; // namespace color

} // namespace deep

#endif
