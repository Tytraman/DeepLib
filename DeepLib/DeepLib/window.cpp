#include "window.hpp"
#include "DeepCore/window.hpp"
#include "DeepLib/context.hpp"

namespace deep
{
    window window::create(const ref<ctx> &context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height)
    {
        window win(context);

        win.m_handle = core_window::create(ctx::get_internal_ctx(context.get()), class_name, title, x, y, width, height);

        return win;
    }
    void window::show()
    {
        core_window::show(m_handle);
    }

    void window::hide()
    {
        core_window::hide(m_handle);
    }

    bool window::process_message()
    {
        return core_window::process_message(ctx::get_internal_ctx(get_context_ptr()), m_handle);
    }
} // namespace deep
