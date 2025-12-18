#include "window.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/memory.hpp"

namespace deep
{
    ref<window> window::create(const ref<ctx> &context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height)
    {
        ref<window> win = ref<window>(context, mem::alloc_type<window>(context.get(), context));

        if (!win.is_valid())
        {
            return win;
        }

        win->m_callbacks      = { 0 };
        win->m_callbacks.data = &win;

        win->m_handle = core_window::create(ctx::get_internal_ctx(context.get()), class_name, title, x, y, width, height, &win->m_callbacks);

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

    void window::set_keydown_callcack(core_window::keydown_callback callback)
    {
        m_callbacks.keydown = callback;
    }

    void window::set_keyup_callback(core_window::keyup_callback callback)
    {
        m_callbacks.keyup = callback;
    }

    void window::set_text_input_callback(core_window::text_input_callback callack)
    {
        m_callbacks.text_input = callack;
    }
} // namespace deep
