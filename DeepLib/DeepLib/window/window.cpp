#include "window.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/memory.hpp"

namespace deep
{
    bool window::keydown_callback(vkey key, bool repeated, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_key_pressed(key, repeated, win);
        }

        return true;
    }

    bool window::keyup_callback(vkey key, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_key_released(key, win);
        }

        return true;
    }

    bool window::text_input_callback(native_char character, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_text_input(character, win);
        }

        return true;
    }

    bool window::lose_focus_callback(void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_lose_focus(win);
        }

        return true;
    }

    window::window(const ref<ctx> &context) noexcept
            : object(context),
              m_keyboard(context),
              m_callbacks(),
              m_handle(invalid_window_handle)
    {
    }

    window::~window() noexcept
    {
        core_window::destroy(ctx::get_internal_ctx(get_context_ptr()), m_handle);
    }

    ref<window> window::create(const ref<ctx> &context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height) noexcept
    {
        ref<window> win = ref<window>(context, mem::alloc_type<window>(context.get(), context));

        if (!win.is_valid())
        {
            return win;
        }

        win->m_callbacks            = { 0 };
        win->m_callbacks.keydown    = keydown_callback;
        win->m_callbacks.keyup      = keyup_callback;
        win->m_callbacks.text_input = text_input_callback;
        win->m_callbacks.lose_focus = lose_focus_callback;
        win->m_callbacks.data       = win.get();

        win->m_handle = core_window::create(ctx::get_internal_ctx(context.get()), class_name, title, x, y, width, height, &win->m_callbacks);

        return win;
    }

    void window::show() noexcept
    {
        core_window::show(m_handle);
    }

    void window::hide() noexcept
    {
        core_window::hide(m_handle);
    }

    bool window::process_message() noexcept
    {
        return core_window::process_message(ctx::get_internal_ctx(get_context_ptr()), m_handle);
    }

    keyboard &window::get_keyboard() noexcept
    {
        return m_keyboard;
    }
} // namespace deep
