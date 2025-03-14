#include "core.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    if (!deep::core::core::create_context(context))
    {
        return 1;
    }

    void *addr = deep::core::mem::alloc(1000);

    if (addr == nullptr)
    {
        return 1;
    }

    addr = deep::core::mem::realloc(addr, 2000);

    if (addr == nullptr)
    {
        return 1;
    }

    if (!deep::core::mem::dealloc(addr))
    {
        return 1;
    }

    if (!deep::core::core::destroy_context(context))
    {
        return 1;
    }

    return 0;
}
