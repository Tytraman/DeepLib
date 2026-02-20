#include "image.hpp"

#include "DeepLib/memory/memory.hpp"
#include "DeepLib/maths/math.hpp"

namespace deep
{
    constexpr usize max_channels  = 4;
    constexpr usize max_bit_depth = 16;

    bool image::apply_horizontal_mirror_effect()
    {
        if (!m_image.is_valid())
        {
            return false;
        }

        uint8 *raw = m_image.get();

        uint8 temp[max_channels * (max_bit_depth / 8)] = { 0 };

        uint32 row;
        uint32 column;
        uint32 rows    = m_height;
        uint32 columns = m_width / 2;

        uint32 pixel_size = m_channels * make_unsigned<int32>((m_bit_depth / 8));

        for (row = 0; row < rows; ++row)
        {
            for (column = 0; column < columns; ++column)
            {
                uint32 index1 = (row * m_width + column) * pixel_size;

                uint32 dest_column = m_width - 1 - column;
                uint32 index2      = (row * m_width + dest_column) * pixel_size;

                memcpy(temp, raw + index1, pixel_size);
                memcpy(raw + index1, raw + index2, pixel_size);
                memcpy(raw + index2, temp, pixel_size);
            }
        }

        return true;
    }

    bool image::apply_vertical_mirror_effect()
    {
        if (!m_image.is_valid())
        {
            return false;
        }

        uint8 *raw = m_image.get();

        uint8 temp[max_channels * (max_bit_depth / 8)] = { 0 };

        uint32 row;
        uint32 column;
        uint32 rows    = m_height / 2;
        uint32 columns = m_width;

        uint32 pixel_size = m_channels * make_unsigned<int32>((m_bit_depth / 8));

        for (row = 0; row < rows; ++row)
        {
            uint32 dest_row = m_height - 1 - row;

            for (column = 0; column < columns; ++column)
            {
                uint32 index1 = (row * columns + column) * pixel_size;
                uint32 index2 = (dest_row * columns + column) * pixel_size;

                memcpy(temp, raw + index1, pixel_size);
                memcpy(raw + index1, raw + index2, pixel_size);
                memcpy(raw + index2, temp, pixel_size);
            }
        }

        return true;
    }

    bool image::apply_palette(const color_rgb *colors, usize number_of_colors)
    {
        if (!m_image.is_valid() || m_color_space != color_space::RGB || m_bit_depth != 8)
        {
            return false;
        }

        uint8 *raw = m_image.get();

        uint32 x, y;
        uint32 rows    = m_height;
        uint32 columns = m_width;

        for (y = 0; y < rows; ++y)
        {
            uint8 *row_ptr = raw + (y * m_row_bytes);

            for (x = 0; x < columns; ++x)
            {
                uint8 *pixel_ptr = row_ptr + (x * m_channels);

                color_rgb pixel = color_rgb(pixel_ptr[0], pixel_ptr[1], pixel_ptr[2]);

                color_rgb closest = color::find_closest_color(pixel, colors, number_of_colors);

                pixel_ptr[0] = closest.x;
                pixel_ptr[1] = closest.y;
                pixel_ptr[2] = closest.z;
            }
        }

        return true;
    }

    bool image::apply_luminance()
    {
        if (!m_image.is_valid() || m_color_space != color_space::RGB || m_bit_depth != 8)
        {
            return false;
        }

        uint8 *raw = m_image.get();

        uint32 x, y;
        uint32 rows    = m_height;
        uint32 columns = m_width;

        for (y = 0; y < rows; ++y)
        {
            uint8 *row_ptr = raw + (y * m_row_bytes);

            for (x = 0; x < columns; ++x)
            {
                uint8 *pixel_ptr = row_ptr + (x * m_channels);

                color_rgb pixel = color_rgb(pixel_ptr[0], pixel_ptr[1], pixel_ptr[2]);

                color_linearized_rgb linearized_pixel = color::linearise(pixel);
                float luminance                       = color::calc_luminance(linearized_pixel);

                color_linearized_rgb new_linearized;

                if (luminance < 0.5f)
                {
                    new_linearized = color_linearized_rgb(0.0f, 0.0f, luminance * 2.0f);
                }
                else
                {
                    new_linearized = color_linearized_rgb(luminance, luminance, 0.0f);
                }

                color_rgb final_color = color::delinearise(new_linearized);

                pixel_ptr[0] = final_color.x;
                pixel_ptr[1] = final_color.y;
                pixel_ptr[2] = final_color.z;
            }
        }

        return true;
    }

    bool image::resize(uint32 width, uint32 height)
    {
        if (!m_image.is_valid())
        {
            return false;
        }

        uint32 pixel_size = m_channels * make_unsigned<int32>((m_bit_depth / 8));

        usize new_bytes_size = width * height * pixel_size;

        memory_manager *manager = m_image.get_memory_manager();
        uint8 *dest             = mem::alloc<uint8>(manager, new_bytes_size);
        const uint8 *from       = m_image.get();

        usize row_bytes     = m_row_bytes;
        usize new_row_bytes = width * pixel_size;

        usize bytes_to_copy = math::min(row_bytes, new_row_bytes);

        uint32 rows = math::min(height, m_height);
        uint32 row;

        for (row = 0; row < rows; ++row)
        {
            memcpy(dest + row * new_row_bytes, from + row * row_bytes, bytes_to_copy);
        }

        mem::dealloc(m_image);

        m_image.set(manager, dest, new_bytes_size);

        m_width     = width;
        m_height    = height;
        m_row_bytes = new_row_bytes;

        return true;
    }

    image image::copy(ctx *context) const
    {
        image to;

        if (!m_image.is_valid())
        {
            return to;
        }

        usize bytes_size = m_image.get_bytes_size();

        uint8 *ptr = mem::alloc<uint8>(context, bytes_size);

        if (ptr == nullptr)
        {
            return to;
        }

        memcpy(ptr, m_image.get(), bytes_size);

        to.m_row_bytes   = m_row_bytes;
        to.m_width       = m_width;
        to.m_height      = m_height;
        to.m_bit_depth   = m_bit_depth;
        to.m_channels    = m_channels;
        to.m_color_space = m_color_space;
        to.m_image.set(context, ptr, bytes_size);

        return to;
    }
} // namespace deep
