#include "lib.hpp"
#include "DeepCore/memory.hpp"

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    void *addr = deep::core_mem::alloc(context->get_internal_ctx(), 1000);

    if (addr == nullptr)
    {
        return 1;
    }

    addr = deep::core_mem::realloc(context->get_internal_ctx(), addr, 2000);

    if (addr == nullptr)
    {
        return 1;
    }

    if (!deep::core_mem::dealloc(context->get_internal_ctx(), addr))
    {
        return 1;
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 1;
    }

    return 0;
}
