#include "memory.hpp"
#include "core.hpp"

namespace deep
{
    void *core_mem::alloc(usize size)
    {
        return core_alloc(core::g_internal_context, size);
    }

    void *core_mem::realloc(void *address, usize size)
    {
        return core_realloc(core::g_internal_context, address, size);
    }

    bool core_mem::dealloc(void *address)
    {
        return core_dealloc(core::g_internal_context, address);
    }
} // namespace deep
