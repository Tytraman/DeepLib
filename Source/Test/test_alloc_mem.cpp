#include "memory.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    void *addr = deep::mem::alloc(context, 1000,
                                  deep::mem::ProtRead | deep::mem::ProtWrite);

    if (addr == nullptr)
    {
        return 1;
    }

    if (!deep::mem::dealloc(context, addr, 1000))
    {
        return 1;
    }

    return 0;
}
