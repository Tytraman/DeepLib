#include "memory.hpp"

namespace deep
{
    void *mem::alloc(ctx &context, usize size)
    {
        return core_alloc(&context.result, size);
    }

    void *mem::realloc(ctx &context, void *address, usize size)
    {
        return core_realloc(&context.result, address, size);
    }

    bool mem::dealloc(ctx &context, void *address)
    {
        return core_dealloc(&context.result, address);
    }
} // namespace deep
