#include "../memory.hpp"
#include "../error.hpp"

#include <Windows.h>

namespace deep
{
    void *core_alloc(uint64 *result, usize size)
    {
        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            *result = core_convert_error_code(GetLastError());

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

    void *core_realloc(uint64 *result, void *address, usize size)
    {
        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            *result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        if (address == nullptr)
        {
            addr = HeapAlloc(process_heap, HEAP_ZERO_MEMORY, size);
        }
        else
        {
            addr = HeapReAlloc(process_heap, HEAP_ZERO_MEMORY, address, size);
        }

        if (addr == nullptr)
        {
            // TODO: récupérer le code d'erreur en cas d'échec
            return nullptr;
        }

        return addr;
    }

    bool core_dealloc(uint64 *result, void *address)
    {
        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            *result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        if (HeapFree(process_heap, 0, address) == 0)
        {
            *result = core_convert_error_code(GetLastError());

            return false;
        }

        return true;
    }
} // namespace deep
