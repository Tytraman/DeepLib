#include "memory.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    void *addr = deep::mem::alloc(context, 1000);

    if (addr == nullptr)
    {
        return 1;
    }

    addr = deep::mem::realloc(context, addr, 2000);

    if (addr == nullptr)
    {
        return 1;
    }

    if (!deep::mem::dealloc(context, addr))
    {
        return 1;
    }

    return 0;
}
