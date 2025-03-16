#include "../memory.hpp"
#include "../error.hpp"
#include "internal_data.hpp"

#include <Windows.h>

namespace deep
{
    void *core_alloc(void *internal_context, usize size)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        return core_alloc(&internal_data->result, size);
    }

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

        *result = error::NoError;

        return addr;
    }

    void *core_realloc(void *internal_context, void *address, usize size)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            internal_data->result = core_convert_error_code(GetLastError());

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

    bool core_dealloc(void *internal_context, void *address)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            internal_data->result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        if (HeapFree(process_heap, 0, address) == 0)
        {
            internal_data->result = core_convert_error_code(GetLastError());

            return false;
        }

        return true;
    }
} // namespace deep
