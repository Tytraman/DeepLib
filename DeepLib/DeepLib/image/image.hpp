#ifndef DEEP_LIB_IMAGE_HPP
#define DEEP_LIB_IMAGE_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"

namespace deep
{
    template class DEEP_LIB_API buffer_ptr<uint8>;

    class DEEP_LIB_API image
    {
      public:
        enum class color_space
        {
            None,
            Gray,
            Palette,
            RGB,
            RGBA,
            GA,
            BGR,
            BGRA
        };

        enum class channel
        {
            Red,
            Green,
            Blue,
            Alpha
        };

      public:
        image() = default;

        static uint8 get_channels(color_space space);

        const uint8 *operator*() const;

        usize get_row_bytes() const;
        uint32 get_width() const;
        uint32 get_height() const;
        int32 get_bit_depth() const;
        uint8 get_channels() const;
        color_space get_color_space() const;

        bool is_valid() const;

      protected:
        buffer_ptr<uint8> m_image;

        usize m_row_bytes;
        uint32 m_width;
        uint32 m_height;
        int32 m_bit_depth;
        uint8 m_channels;
        color_space m_color_space;

      public:
        friend class png;
    };

    inline uint8 image::get_channels(color_space space)
    {
        switch (space)
        {
            default:
                return 0;
            case color_space::Gray:
                return 1;
            case color_space::Palette:
                return 1;
            case color_space::RGB:
                return 3;
            case color_space::BGR:
                return 3;
            case color_space::RGBA:
                return 4;
            case color_space::GA:
                return 2;
            case color_space::BGRA:
                return 4;
        }
    }

    inline const uint8 *image::operator*() const
    {
        return m_image.get();
    }

    inline usize image::get_row_bytes() const
    {
        return m_row_bytes;
    }

    inline uint32 image::get_width() const
    {
        return m_width;
    }

    inline uint32 image::get_height() const
    {
        return m_height;
    }

    inline int32 image::get_bit_depth() const
    {
        return m_bit_depth;
    }

    inline uint8 image::get_channels() const
    {
        return m_channels;
    }

    inline image::color_space image::get_color_space() const
    {
        return m_color_space;
    }

    inline bool image::is_valid() const
    {
        return m_image.is_valid();
    }
} // namespace deep

#endif
