#ifndef DEEP_CORE_CORE_HPP
#define DEEP_CORE_CORE_HPP

#include "context.hpp"
#include "filesystem.hpp"
#include "memory.hpp"

namespace deep
{
    namespace core
    {
        class DEEP_CORE_API core
        {
          public:
            static bool create_context(ctx &context);
            static bool destroy_context(ctx &context);

            static void set_current_context(ctx &context);
            static ctx &get_current_context();
            static ctx *get_current_context_ptr();

          private:
            static ctx *g_current_context;

            friend mem;
            friend fs;
        };

        inline void core::set_current_context(ctx &context)
        {
            g_current_context = &context;
        }

        inline ctx &core::get_current_context()
        {
            return *g_current_context;
        }

        inline ctx *core::get_current_context_ptr()
        {
            return g_current_context;
        }
    } // namespace core

} // namespace deep

#endif
