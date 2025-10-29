#include "memory.hpp"

namespace deep
{
    void *core_mem::alloc(void *internal_context, usize size)
    {
        return core_alloc(internal_context, size);
    }

    void *core_mem::realloc(void *internal_context, void *address, usize size)
    {
        return core_realloc(internal_context, address, size);
    }

    bool core_mem::dealloc(void *internal_context, void *address)
    {
        return core_dealloc(internal_context, address);
    }
} // namespace deep
