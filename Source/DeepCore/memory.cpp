#include "memory.hpp"

namespace deep
{
    void *mem::alloc(ctx &context, usize size, uint8 protection)
    {
        return core_alloc(context, size, protection);
    }

    bool mem::dealloc(ctx &context, void *address, usize size)
    {
        return core_dealloc(context, address, size);
    }
} // namespace deep
