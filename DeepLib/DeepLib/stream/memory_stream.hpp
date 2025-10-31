#ifndef DEEP_LIB_MEMORY_STREAM_HPP
#define DEEP_LIB_MEMORY_STREAM_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/stream/stream.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"

namespace deep
{
    template class DEEP_LIB_API buffer_ptr<uint8>;

    class DEEP_LIB_API memory_stream : public stream
    {
      public:
        memory_stream(ctx *context);

        virtual bool open() override;
        virtual bool close() override;
        virtual bool flush() override;

        virtual bool can_read() const override;
        virtual bool can_write() const override;
        virtual bool can_timeout() const override;
        virtual bool can_seek() const override;

        virtual usize get_length() const override;
        virtual bool set_length(usize length) override;

        virtual usize get_position() const override;

        virtual uint32 get_read_timeout() const override;
        virtual uint32 get_write_timeout() const override;

        virtual void set_read_timeout(uint32 value) override;
        virtual void set_write_timeout(uint32 value) override;

        virtual usize seek(isize offset, seek_origin origin) override;

        virtual bool read(void *dest, usize count, usize *bytes_read) override;
        virtual bool write(void *src, usize count, usize *bytes_written) override;

        virtual bool copy_to(stream &other) override;

        virtual bool is_opened() const override;

        uint8 *get();
        const uint8 *get() const;

      protected:
        buffer_ptr<uint8> m_buffer;
        usize m_position;
    };

    inline uint8 *memory_stream::get()
    {
        return m_buffer.get();
    }

    inline const uint8 *memory_stream::get() const
    {
        return m_buffer.get();
    }
} // namespace deep

#endif
