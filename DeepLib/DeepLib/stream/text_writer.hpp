#ifndef DEEP_LIB_TEXT_WRITER_HPP
#define DEEP_LIB_TEXT_WRITER_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/object.hpp"

namespace deep
{
    class DEEP_LIB_API text_writer : public object
    {
      public:
        using object::object;

        virtual bool open()  = 0;
        virtual bool close() = 0;

        virtual bool write(bool value)             = 0;
        virtual bool write(const char *str)        = 0;
        virtual bool write(const native_char *str) = 0;
        virtual bool write(int32 value)            = 0;
        virtual bool write(uint32 value)           = 0;
        virtual bool write(int64 value)            = 0;
        virtual bool write(uint64 value)           = 0;
        virtual bool write(double value)           = 0;

        virtual bool is_opened() = 0;

        text_writer &operator<<(bool value);
        text_writer &operator<<(const char *str);
        text_writer &operator<<(const native_char *str);
        text_writer &operator<<(int32 value);
        text_writer &operator<<(uint32 value);
        text_writer &operator<<(int64 value);
        text_writer &operator<<(uint64 value);
        text_writer &operator<<(double value);
    };
} // namespace deep

#endif
