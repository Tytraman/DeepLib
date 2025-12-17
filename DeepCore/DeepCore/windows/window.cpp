#include "../window.hpp"
#include "../error.hpp"
#include "internal_data.hpp"

namespace deep
{
    LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
            default:
                break;
            case WM_CLOSE:
            {
                PostQuitMessage(0);
            }
            break;
        }

        return DefWindowProcW(hwnd, msg, wparam, lparam);
    }

    window_handle core_window_create(void *internal_context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        HMODULE instance = GetModuleHandleA(nullptr);

        if (instance == nullptr)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return nullptr;
        }

        WNDCLASSEXW wc   = { 0 };
        wc.cbSize        = sizeof(wc);
        wc.style         = CS_OWNDC;
        wc.lpfnWndProc   = window_proc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = instance;
        wc.hIcon         = nullptr;
        wc.hCursor       = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName  = nullptr;
        wc.lpszClassName = class_name;
        wc.hIconSm       = nullptr;

        ATOM registered_class = RegisterClassExW(&wc);

        if (registered_class == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return nullptr;
        }

        window_handle hwnd = CreateWindowExW(
                0,
                class_name,
                title,
                WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
                x, y, width, height,
                nullptr,
                nullptr,
                instance,
                nullptr);

        if (hwnd == nullptr)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return nullptr;
        }

        return hwnd;
    }

    void core_window_show(window_handle win)
    {
        ShowWindow(win, SW_SHOW);
    }

    void core_window_hide(window_handle win)
    {
        ShowWindow(win, SW_HIDE);
    }

    bool core_window_process_message(void *internal_context, window_handle /*win*/)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        MSG message;

        BOOL result = GetMessageW(&message, nullptr, 0, 0);

        if (result == -1)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        if (result == 0)
        {
            return false;
        }

        TranslateMessage(&message);
        DispatchMessageW(&message);

        return true;
    }
} // namespace deep
