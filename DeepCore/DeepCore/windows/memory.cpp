#include "../memory.hpp"
#include "../error.hpp"
#include "internal_data.hpp"

#include <Windows.h>

namespace deep
{
    void *core_alloc(void *internal_context, usize size)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return nullptr;
        }

        addr = HeapAlloc(process_heap, HEAP_ZERO_MEMORY, size);

        if (addr == nullptr)
        {
            // TODO: récupérer le code d'erreur en cas d'échec
            return nullptr;
        }

        if (internal_data != nullptr)
        {
            internal_data->result = error::NoError;
        }

        return addr;
    }

    void *core_realloc(void *internal_context, void *address, usize size)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        LPVOID addr;

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

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

        if (internal_data != nullptr)
        {
            internal_data->result = error::NoError;
        }

        return addr;
    }

    bool core_dealloc(void *internal_context, void *address)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        HANDLE process_heap = GetProcessHeap();

        if (process_heap == nullptr)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        if (HeapFree(process_heap, 0, address) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        if (internal_data != nullptr)
        {
            internal_data->result = error::NoError;
        }

        return true;
    }
} // namespace deep
