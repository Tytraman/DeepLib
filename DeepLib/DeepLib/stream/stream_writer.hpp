#ifndef DEEP_LIB_STREAM_WRITER_HPP
#define DEEP_LIB_STREAM_WRITER_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/stream/stream.hpp"
#include "DeepLib/stream/text_writer.hpp"

namespace deep
{
    class DEEP_LIB_API stream_writer : public text_writer
    {
      public:
        stream_writer(const ref<ctx> &context, stream *s);

        virtual bool open() override;
        virtual bool close() override;

        virtual bool write(bool value) override;
        virtual bool write(const char *str) override;
        virtual bool write(const native_char *str) override;
        virtual bool write(int32 value) override;
        virtual bool write(uint32 value) override;
        virtual bool write(int64 value) override;
        virtual bool write(uint64 value) override;
        virtual bool write(double value) override;

        virtual bool is_opened() override;

      protected:
        DEEP_REF(stream, m_stream)
    };
} // namespace deep

#endif
