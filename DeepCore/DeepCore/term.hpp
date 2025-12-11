#ifndef DEEP_CORE_TERM_HPP
#define DEEP_CORE_TERM_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_term
    {
      public:
        enum class std_handle
        {
            Input,
            Output,
            Error
        };

        enum class mode
        {
            EnableProcessedOutput,
            EnableVirtualTerminalProcessing
        };

      public:
        static fd get_std_handle(void *internal_context, std_handle h);
        static bool set_encoding(void *internal_context, string_encoding encoding);
        static bool add_mode(void *internal_context, fd std, mode m);
    };

    extern fd core_term_get_std_handle(void *internal_context, core_term::std_handle h);
    extern bool core_term_set_encoding(void *internal_context, string_encoding encoding);
    extern bool core_term_add_mode(void *internal_context, fd std, core_term::mode m);
} // namespace deep

#endif
