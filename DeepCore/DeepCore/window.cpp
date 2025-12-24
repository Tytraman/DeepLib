#include "window.hpp"

namespace deep
{
    window_handle core_window::create(void *internal_context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height, callbacks *call)
    {
        return core_window_create(internal_context, class_name, title, x, y, width, height, call);
    }

    bool core_window::destroy(void *internal_context, window_handle win)
    {
        return core_window_destroy(internal_context, win);
    }

    void core_window::show(window_handle win)
    {
        core_window_show(win);
    }

    void core_window::hide(window_handle win)
    {
        core_window_hide(win);
    }

    bool core_window::process_message(void *internal_context, window_handle win)
    {
        return core_window_process_message(internal_context, win);
    }
} // namespace deep
