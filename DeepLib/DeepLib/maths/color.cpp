#include "color.hpp"

#include <algorithm>
#include <cmath>

namespace deep
{
    float srgb_to_linear_channel(float norm_value)
    {
        if (norm_value <= 0.04045f)
        {
            return norm_value / 12.92f;
        }
        else
        {
            return std::pow((norm_value + 0.055f) / 1.055f, 2.4f);
        }
    }

    uint8 linear_to_srgb_channel(float value)
    {
        float val = 0.0f;

        if (value <= 0.0031308f)
        {
            val = value * 12.92f;
        }
        else
        {
            val = 1.055f * std::pow(value, 1.0f / 2.4f) - 0.055f;
        }

        val = val * 255.0f;

        return static_cast<uint8>(std::clamp(val + 0.5f, 0.0f, 255.0f));
    }

    color_rgb color::find_closest_color(const color_rgb &color, const color_rgb *colors, usize number_of_colors)
    {
        float min_distance = 50000.0f;
        usize index_color  = 0;
        usize index;

        float color_length = color_rgb::magn(color);

        for (index = 0; index < number_of_colors; ++index)
        {
            color_rgb color1, color2;

            if (color_length > color_rgb::magn(colors[index]))
            {
                color1 = color;
                color2 = colors[index];
            }
            else
            {
                color1 = colors[index];
                color2 = color;
            }

            color_rgb c = color1 - color2;

            float distance = color_rgb::magn(c);

            if (distance < min_distance)
            {
                min_distance = distance;
                index_color  = index;
            }
        }

        return colors[index_color];
    }

    color_linearized_rgb color::linearise(const color_rgb &color)
    {
        constexpr float val = 255.0f;

        float r_norm = color.x / val;
        float g_norm = color.y / val;
        float b_norm = color.z / val;

        return color_linearized_rgb(
                srgb_to_linear_channel(r_norm),
                srgb_to_linear_channel(g_norm),
                srgb_to_linear_channel(b_norm));
    }

    color_rgb color::delinearise(const color_linearized_rgb &color)
    {
        return color_rgb(
                linear_to_srgb_channel(color.x),
                linear_to_srgb_channel(color.y),
                linear_to_srgb_channel(color.z));
    }

    float color::calc_luminance(const color_linearized_rgb &color)
    {
        color_linearized_rgb values = color_linearized_rgb(0.2126f, 0.7152f, 0.0722f);

        return color_linearized_rgb::dot(color, values);
    }
} // namespace deep
