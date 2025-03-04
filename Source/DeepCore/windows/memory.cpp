#include "../memory.hpp"
#include "../error.hpp"

#include <Windows.h>

namespace deep
{
    void *core_alloc(ctx &context, usize size)
    {
        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            context.result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        addr = HeapAlloc(process_heap, HEAP_ZERO_MEMORY, size);

        if (addr == nullptr)
        {
            // TODO: récupérer le code d'erreur en cas d'échec
            return nullptr;
        }

        return addr;
    }

    void *core_realloc(ctx &context, void *address, usize size)
    {
        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            context.result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        addr = HeapReAlloc(process_heap, HEAP_ZERO_MEMORY, address, size);

        if (addr == nullptr)
        {
            // TODO: récupérer le code d'erreur en cas d'échec
            return nullptr;
        }

        return addr;
    }

    bool core_dealloc(ctx &context, void *address)
    {
        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            context.result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        if (HeapFree(process_heap, 0, address) == 0)
        {
            context.result = core_convert_error_code(GetLastError());

            return false;
        }

        return true;
    }
} // namespace deep
