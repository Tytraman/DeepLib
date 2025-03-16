#include "DeepCore/memory.hpp"
#include "lib.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    if (!deep::lib::create_context(context))
    {
        return 1;
    }

    void *addr = deep::core_mem::alloc(1000);

    if (addr == nullptr)
    {
        return 1;
    }

    addr = deep::core_mem::realloc(addr, 2000);

    if (addr == nullptr)
    {
        return 1;
    }

    if (!deep::core_mem::dealloc(addr))
    {
        return 1;
    }

    if (!deep::lib::destroy_context())
    {
        return 1;
    }

    return 0;
}
