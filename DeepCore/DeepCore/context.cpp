#include "context.hpp"

namespace deep
{
    void *core_ctx::create_internal_ctx()
    {
        return core_create_internal_ctx();
    }

    bool core_ctx::destroy_internal_ctx(void *internal_ctx)
    {
        return core_destroy_internal_ctx(internal_ctx);
    }

    uint64 core_ctx::get_internal_ctx_result(void *internal_ctx)
    {
        return core_get_internal_ctx_result(internal_ctx);
    }

    void core_ctx::set_internal_ctx_result(void *internal_ctx, uint64 result)
    {
        core_set_internal_ctx_result(internal_ctx, result);
    }
} // namespace deep
