#ifndef DEEP_CORE_CORE_HPP
#define DEEP_CORE_CORE_HPP

#include "context.hpp"

namespace deep
{

    class DEEP_CORE_API core
    {
      public:
        static ctx *create_context();
        static bool destroy_context(ctx *context);

        static void set_current_context(ctx *context);
        static ctx *get_current_context();

      private:
        static ctx *g_current_context;
    };

    inline void core::set_current_context(ctx *context)
    {
        g_current_context = context;
    }

    inline ctx *core::get_current_context()
    {
        return g_current_context;
    }

} // namespace deep

#endif
