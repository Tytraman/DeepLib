#ifndef DEEP_LIB_STREAM_HPP
#define DEEP_LIB_STREAM_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/object.hpp"

namespace deep
{
    class DEEP_LIB_API stream : public object
    {
      public:
        enum class seek_origin
        {
            Begin,
            Current,
            End
        };

      public:
        using object::object;

        virtual bool open()  = 0;
        virtual bool close() = 0;
        virtual bool flush() = 0;

        virtual bool can_read() const    = 0;
        virtual bool can_write() const   = 0;
        virtual bool can_timeout() const = 0;
        virtual bool can_seek() const    = 0;

        virtual usize get_length() const      = 0;
        virtual bool set_length(usize length) = 0;

        virtual usize get_position() const = 0;

        virtual uint32 get_read_timeout() const  = 0;
        virtual uint32 get_write_timeout() const = 0;

        virtual void set_read_timeout(uint32 value)  = 0;
        virtual void set_write_timeout(uint32 value) = 0;

        virtual usize seek(isize offset, seek_origin origin) = 0;

        virtual bool read(void *dest, usize count, usize *bytes_read)          = 0;
        virtual bool write(const void *src, usize count, usize *bytes_written) = 0;

        virtual bool copy_to(stream &other) = 0;

        virtual bool is_opened() const = 0;

      protected:
        stream() = default;
    };
} // namespace deep

#endif
