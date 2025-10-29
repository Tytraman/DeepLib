#include "../memory.hpp"
#include "../error.hpp"
#include <cerrno>
#include <sys/mman.h>

namespace deep
{
    void *core_alloc(ctx &context, usize size, uint8 protection)
    {
        int prot = 0;
        void *addr;

        if (protection == mem::ProtNone)
        {
            prot = PROT_NONE;
        }
        else
        {
            if (protection & mem::ProtRead)
            {
                prot |= PROT_READ;
            }

            if (protection & mem::ProtWrite)
            {
                prot |= PROT_WRITE;
            }

            if (protection & mem::ProtExec)
            {
                prot |= PROT_EXEC;
            }
        }

        addr = mmap(nullptr, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        if (addr == MAP_FAILED)
        {
            context.result = core_convert_error_code(errno);

            return nullptr;
        }

        context.result = error::NoError;

        return addr;
    }

    bool core_dealloc(ctx &context, void *address, usize size)
    {
        if (munmap(address, size) != 0)
        {
            context.result = core_convert_error_code(errno);

            return false;
        }

        context.result = error::NoError;

        return true;
    }
} // namespace deep
