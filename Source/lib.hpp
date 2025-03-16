#ifndef DEEP_LIB_HPP
#define DEEP_LIB_HPP

#include "DeepCore/core.hpp"
#include "context.hpp"
#include "deep_lib_export.h"

namespace deep
{
    class DEEP_LIB_API lib
    {
      public:
        static const char *get_version();

        static bool create_context(ctx &context);
        static bool destroy_context();
        static void set_current_context(ctx &context);

        static ctx &get_current_context();
        static ctx *get_current_context_ptr();

        static uint64 get_context_result();

      private:
        static ctx *g_current_context;
    };

    inline void lib::set_current_context(ctx &context)
    {
        g_current_context = &context;

        core::set_current_internal_context(g_current_context->internal_data);
    }

    inline ctx &lib::get_current_context()
    {
        return *g_current_context;
    }

    inline ctx *lib::get_current_context_ptr()
    {
        return g_current_context;
    }
} // namespace deep

#endif
