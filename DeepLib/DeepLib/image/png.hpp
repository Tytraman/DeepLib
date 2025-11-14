#ifndef DEEP_LIB_PNG_HPP
#define DEEP_LIB_PNG_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/string/string.hpp"
#include "DeepLib/stream/stream.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"
#include "DeepLib/image/image.hpp"

#include <png.h>

namespace deep
{
    template class DEEP_LIB_API buffer_ptr<uint8>;

    class DEEP_LIB_API png
    {
      public:
        static png load(ctx *context, stream *input);
        static bool convert(const image &from, stream *output);

        static string get_libpng_version(ctx *context);

        bool check() const;
        bool read_info();
        image read_image();

        usize get_position() const;
        usize get_bytes_size() const;

        buffer_ptr<uint8> &get_buffer();

        uint32 get_width() const;
        uint32 get_height() const;

        void set_position(usize position);

        bool is_valid() const;

      protected:
        png() = default;

      protected:
        ctx *m_context;
        buffer_ptr<uint8> m_data;
        usize m_position;

        png_structp m_png;
        png_infop m_info;

        uint32 m_width;
        uint32 m_height;
        int m_bit_depth;
        int m_color_type;
        int m_interlace_type;
    };

    inline usize png::get_position() const
    {
        return m_position;
    }

    inline usize png::get_bytes_size() const
    {
        return m_data.get_bytes_size();
    }

    inline buffer_ptr<uint8> &png::get_buffer()
    {
        return m_data;
    }

    inline uint32 png::get_width() const
    {
        return m_width;
    }

    inline uint32 png::get_height() const
    {
        return m_height;
    }

    inline void png::set_position(usize position)
    {
        m_position = position;
    }

    inline bool png::is_valid() const
    {
        return m_data.is_valid();
    }
} // namespace deep

#endif
