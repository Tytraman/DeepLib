#include "../thread.hpp"
#include "../error.hpp"
#include "internal_data.hpp"

namespace deep
{
    handle core_create_thread(void *internal_context, native_thread_callback callback, void *args, bool paused)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DWORD creation_flags = 0;
        DWORD id;

        if (paused)
        {
            creation_flags |= CREATE_SUSPENDED;
        }

        handle h = CreateThread(nullptr, 0, callback, args, creation_flags, &id);

        if (h == nullptr)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return nullptr;
        }

        return h;
    }

    bool core_suspend_thread(void *internal_context, handle thread)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DWORD count = SuspendThread(thread);

        if (count == static_cast<DWORD>(-1))
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        return true;
    }

    bool core_resume_thread(void *internal_context, handle thread)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DWORD count = ResumeThread(thread);

        if (count == static_cast<DWORD>(-1))
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        return true;
    }

    void core_wait_thread(handle thread, uint32 milliseconds)
    {
        WaitForSingleObject(thread, milliseconds);
    }

    DWORD WINAPI core_native_thread(LPVOID lpParameter)
    {
        core_thread::native_args *args = static_cast<core_thread::native_args *>(lpParameter);

        if (args != nullptr && args->callback != nullptr)
        {
            args->callback(args->args);
        }

        return 0;
    }
} // namespace deep
