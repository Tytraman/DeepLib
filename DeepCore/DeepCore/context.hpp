#ifndef DEEP_CORE_CONTEXT_HPP
#define DEEP_CORE_CONTEXT_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_ctx
    {
      public:
        static void *create_internal_ctx();
        static bool destroy_internal_ctx(void *internal_ctx);
        static uint64 get_internal_ctx_result(void *internal_ctx);
        static void set_internal_ctx_result(void *internal_ctx, uint64 result);
    };

    extern void *core_create_internal_ctx();
    extern bool core_destroy_internal_ctx(void *internal_ctx);
    extern uint64 core_get_internal_ctx_result(void *internal_ctx);
    extern void core_set_internal_ctx_result(void *internal_ctx, uint64 result);
} // namespace deep

#endif
