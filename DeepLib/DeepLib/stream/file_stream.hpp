#ifndef DEEP_LIB_FILE_STREAM_HPP
#define DEEP_LIB_FILE_STREAM_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/context.hpp"
#include "DeepLib/stream/stream.hpp"
#include "DeepLib/string/string_native.hpp"
#include "DeepCore/filesystem.hpp"

namespace deep
{

    class DEEP_LIB_API file_stream : public stream
    {
      public:
        file_stream(const ref<ctx> &context, const native_char *filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share);
        file_stream(const ref<ctx> &context, string_native &filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share);
        ~file_stream();

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
        virtual bool write(const void *src, usize count, usize *bytes_written) override;

        virtual bool copy_to(stream &other) override;

        virtual bool is_opened() const override;

      protected:
        string_native m_filename;
        core_fs::file_mode m_mode;
        core_fs::file_access m_access;
        core_fs::file_share m_share;
        fd m_fd;
        bool m_is_opened;
    };
} // namespace deep

#endif
