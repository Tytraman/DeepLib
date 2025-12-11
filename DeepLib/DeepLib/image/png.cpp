#include "png.hpp"

namespace deep
{
    void png_user_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        // Permet de récupérer le pointeur de données lié à la structure PNG.
        png *mypng      = reinterpret_cast<png *>(png_get_io_ptr(png_ptr));
        size_t position = mypng->get_position();

        // Vérifie qu'il y a suffisamment d'octets à lire.
        if (position + length > mypng->get_bytes_size())
        {
            png_error(png_ptr, "png_user_read_data: cannot read more data");
            return;
        }

        buffer_ptr<uint8> &buffer = mypng->get_buffer();

        if (!buffer.is_valid())
        {
            png_error(png_ptr, "png_user_read_data: buffer is not valid");
            return;
        }

        memcpy(data, buffer.get() + position, length);

        mypng->set_position(position + length);
    }

    void png_user_write_data_to_stream(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        stream *output = reinterpret_cast<stream *>(png_get_io_ptr(png_ptr));

        if (!output->write(data, length, nullptr))
        {
            png_error(png_ptr, "png_user_write_data_to_stream: error writting to stream");
            return;
        }
    }

    void png_user_flush_memory(png_structp /* png_ptr */)
    {
    }

    png png::load(const ref<ctx> &context, stream *input)
    {
        png out;

        if (input == nullptr || !input->can_read())
        {
            return out;
        }

        usize length     = input->get_length();
        usize position   = input->get_position();
        usize bytes_size = length - position;

        uint8 *buffer = mem::alloc<uint8>(context.get(), bytes_size);

        if (buffer == nullptr)
        {
            return out;
        }

        if (!input->read(buffer, bytes_size, nullptr))
        {
            mem::dealloc(context.get(), buffer);

            return out;
        }

        out.m_context = context.get();
        out.m_data.set(context.get(), buffer, bytes_size);

        return out;
    }

    bool png::convert(const image &from, stream *output)
    {
        png_structp png_ptr;
        png_infop info_ptr;

        if (output == nullptr || !output->can_write())
        {
            return false;
        }

        int color_type;
        switch (from.get_color_space())
        {
            case image::color_space::Gray:
            case image::color_space::Palette:
            default:
                return false;
            case image::color_space::RGB:
            {
                color_type = PNG_COLOR_TYPE_RGB;
            }
            break;
            case image::color_space::RGBA:
            {
                color_type = PNG_COLOR_TYPE_RGBA;
            }
            break;
            case image::color_space::GA:
            {
                color_type = PNG_COLOR_TYPE_GA;
            }
            break;
        }

        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (png_ptr == nullptr)
        {
            return false;
        }

        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == nullptr)
        {
            png_destroy_write_struct(&png_ptr, nullptr);

            return false;
        }

        png_set_write_fn(png_ptr, output, png_user_write_data_to_stream, png_user_flush_memory);

        png_set_IHDR(png_ptr, info_ptr, from.get_width(), from.get_height(), from.get_bit_depth(), color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);

        const uint8 *raw = *from;

        usize row;
        usize height    = from.get_height();
        usize row_bytes = from.get_row_bytes();

        for (row = 0; row < height; ++row)
        {
            png_write_row(png_ptr, raw + row * row_bytes);
        }

        png_destroy_write_struct(&png_ptr, &info_ptr);

        return true;
    }

    string png::get_libpng_version(const ref<ctx> &context)
    {
        return string(context, DEEP_TEXT_UTF8(PNG_LIBPNG_VER_STRING));
    }

    bool png::check() const
    {
        return png_sig_cmp(static_cast<png_const_bytep>(m_data.get()), 0, 4) == 0;
    }

    bool png::read_info()
    {
        m_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (m_png == nullptr)
        {
            return false;
        }

        m_info = png_create_info_struct(m_png);
        if (m_info == nullptr)
        {
            png_destroy_read_struct(&m_png, nullptr, nullptr);

            return false;
        }

        png_set_read_fn(m_png, this, png_user_read_data);

        png_set_sig_bytes(m_png, 4);
        m_position = 4;

        png_read_info(m_png, m_info);

        png_get_IHDR(m_png, m_info, &m_width, &m_height, &m_bit_depth, &m_color_type, &m_interlace_type, nullptr, nullptr);

        return true;
    }

    image png::read_image()
    {
        image img;

        size_t row_bytes = png_get_rowbytes(m_png, m_info);
        uint8 channels   = png_get_channels(m_png, m_info);
        uint32 row;

        usize bytes_size  = row_bytes * m_height;
        uint8 *image_data = mem::alloc<uint8>(m_context, bytes_size);
        if (image_data == nullptr)
        {
            return img;
        }

        for (row = 0; row < m_height; ++row)
        {
            png_read_row(m_png, image_data + row * row_bytes, nullptr);
        }

        png_read_end(m_png, m_info);

        image::color_space color_space;

        switch (m_color_type)
        {
            default:
            {
                color_space = image::color_space::None;
            }
            break;
            case PNG_COLOR_TYPE_GRAY:
            {
                color_space = image::color_space::Gray;
            }
            break;
            case PNG_COLOR_TYPE_PALETTE:
            {
                color_space = image::color_space::Palette;
            }
            break;
            case PNG_COLOR_TYPE_RGB:
            {
                color_space = image::color_space::RGB;
            }
            break;
            case PNG_COLOR_TYPE_RGBA:
            {
                color_space = image::color_space::RGBA;
            }
            break;
            case PNG_COLOR_TYPE_GA:
            {
                color_space = image::color_space::GA;
            }
            break;
        }

        img.m_row_bytes   = row_bytes;
        img.m_width       = m_width;
        img.m_height      = m_height;
        img.m_bit_depth   = m_bit_depth;
        img.m_channels    = channels;
        img.m_color_space = color_space;
        img.m_image.set(m_context, image_data, bytes_size);

        return img;
    }
} // namespace deep
