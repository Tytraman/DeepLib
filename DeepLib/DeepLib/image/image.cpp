#include "image.hpp"

#include "DeepLib/memory/memory.hpp"

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

        uint32 pixel_size = m_channels * (m_bit_depth / 8);

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

        uint32 pixel_size = m_channels * (m_bit_depth / 8);

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
