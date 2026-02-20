#include "window.hpp"

namespace deep
{
    window_handle core_window::create(void *internal_context, const native_char *class_name, const native_char *title, style s, bool transparent, int32 x, int32 y, int32 width, int32 height, callbacks *call) noexcept
    {
        return core_window_create(internal_context, class_name, title, s, transparent, x, y, width, height, call);
    }

    bool core_window::destroy(void *internal_context, window_handle win) noexcept
    {
        return core_window_destroy(internal_context, win);
    }

    void core_window::show(window_handle win) noexcept
    {
        core_window_show(win);
    }

    void core_window::hide(window_handle win) noexcept
    {
        core_window_hide(win);
    }

    void core_window::set_capture(window_handle win) noexcept
    {
        core_window_set_capture(win);
    }

    bool core_window::release_capture(void *internal_context, window_handle win) noexcept
    {
        return core_window_release_capture(internal_context, win);
    }

    void core_window::hide_cursor() noexcept
    {
        core_window_hide_cursor();
    }

    void core_window::show_cursor() noexcept
    {
        core_window_show_cursor();
    }

    bool core_window::set_title(void *internal_context, window_handle win, const native_char *title) noexcept
    {
        return core_window_set_title(internal_context, win, title);
    }

    bool core_window::process_message(void *internal_context, window_handle win) noexcept
    {
        return core_window_process_message(internal_context, win);
    }
} // namespace deep
