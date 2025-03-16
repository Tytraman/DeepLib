#include "core.hpp"

namespace deep
{
    void *core::g_internal_context = nullptr;

    void *core::create_internal_context()
    {
        return core_create_internal_context();
    }

    bool core::destroy_internal_context()
    {
        return core_destroy_internal_context(g_internal_context);
    }

    uint64 core::get_internal_context_result()
    {
        return core_get_internal_context_result(g_internal_context);
    }

    void core::set_internal_context_result(uint64 result)
    {
        core_set_internal_context_result(g_internal_context, result);
    }
} // namespace deep
