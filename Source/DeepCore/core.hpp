#ifndef DEEP_CORE_HPP
#define DEEP_CORE_HPP

#include "deep_core_export.h"
#include "filesystem.hpp"
#include "memory.hpp"
#include "types.hpp"

namespace deep
{
    class DEEP_CORE_API core
    {
      public:
        static void *create_internal_context();
        static bool destroy_internal_context();
        static void set_current_internal_context(void *internal_context);

        static uint64 get_internal_context_result();
        static void set_internal_context_result(uint64 result);

      private:
        static void *g_internal_context;

        friend core_mem;
        friend core_fs;
    };

    extern void *core_create_internal_context();
    extern bool core_destroy_internal_context(void *internal_context);
    extern uint64 core_get_internal_context_result(void *internal_context);
    extern void core_set_internal_context_result(void *internal_context, uint64 result);

    inline void core::set_current_internal_context(void *internal_context)
    {
        g_internal_context = internal_context;
    }

} // namespace deep

#endif
