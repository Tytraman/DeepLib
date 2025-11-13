#include "png.hpp"

namespace deep
{
    void png_user_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        // Permet de récupérer le pointeur de données lié à la structure PNG.
        png *mypng      = (png *) png_get_io_ptr(png_ptr);
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

        // Copie les données dans le buffer libpng.
        memcpy(data, buffer.get() + position, length);

        mypng->set_position(position + length);
    }

    png png::load(ctx *context, stream *input)
    {
        png out;

        if (input == nullptr || !input->can_read())
        {
            return out;
        }

        usize length     = input->get_length();
        usize position   = input->get_position();
        usize bytes_size = length - position;

        uint8 *buffer = mem::alloc<uint8>(context, bytes_size);

        if (buffer == nullptr)
        {
            return out;
        }

        if (!input->read(buffer, bytes_size, nullptr))
        {
            mem::dealloc(context, buffer);

            return out;
        }

        out.m_context = context;
        out.m_data.set(context, buffer, bytes_size);

        return out;
    }

    string png::get_libpng_version(ctx *context)
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

        m_channels = png_get_channels(m_png, m_info);

        return true;
    }

    bool png::read_image()
    {
        uint32 row;
        png_bytep *row_ptr = mem::alloc<png_bytep>(m_context, sizeof(png_bytep) * m_height);

        if (row_ptr == nullptr)
        {
            return false;
        }

        int pass;

        int number_passed =
#ifdef PNG_READ_INTERLACING_SUPPORTED
                png_set_interlace_handling(m_png);
#else
                1;
#endif

        // Pour chaque ligne de l'image.
        for (row = 0; row < m_height; ++row)
        {
            size_t row_size = png_get_rowbytes(m_png, m_info);

            // TODO: vérifier que de la mémoire est allouée pour chaque ligne
            *(row_ptr + row) = mem::alloc<png_byte>(m_context, row_size);
        }

        for (pass = 0; pass < number_passed; ++pass)
        {
            for (row = 0; row < m_height; ++row)
            {
                png_read_rows(m_png, row_ptr + row, nullptr, 1);
            }
        }

        png_read_end(m_png, m_info);

        m_image = reinterpret_cast<uint8 *>(row_ptr);

        return true;
    }
} // namespace deep
